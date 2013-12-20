#include "embeddedmediapostprocessor.h"

#include <QDebug>
#include <QEventLoop>
#include <QString>

#include <oembedmanager.h>
#include <request.h>
#include <response.h>
using qoembed::OEmbedManager;
using qoembed::Request;
using qoembed::Response;

QRegularExpression EmbeddedMediaPostprocessor::re("<a href=\"(.*)\" class=\"embed\">(.*)</a>");

EmbeddedMediaPostprocessor::EmbeddedMediaPostprocessor(QObject *parent) :
    QObject(parent),
    HtmlPostprocessor(),
    manager(new OEmbedManager(this))
{
    qDebug() << "connect to finished signal of OEmbedManager";
    connect(manager, SIGNAL(finished(qoembed::Response*)),
            SLOT(finished(qoembed::Response*)));
}

EmbeddedMediaPostprocessor::~EmbeddedMediaPostprocessor()
{
    qDebug() << "EmbeddedMediaPostprocessor destructor";
}

void EmbeddedMediaPostprocessor::doProcessHtml(QString &html)
{
    if (html.count(re) > 0) {
        QRegularExpressionMatch match = re.match(html);
        while (match.hasMatch()) {
            QString newHtml = fetchResourceFromUrl(match.captured(1));
            html.replace(match.capturedStart(), match.capturedLength(), newHtml);

            match = re.match(html);
        }
    }
}

void EmbeddedMediaPostprocessor::finished(qoembed::Response *response)
{
    result = response->render();
}

QString EmbeddedMediaPostprocessor::fetchResourceFromUrl(const QString &url)
{
    if (resultCache.contains(url)) {
        result = resultCache.value(url);
    } else {
        qDebug() << "fetch resource";
        manager->fetch(Request::createForUrl(QUrl(url)));

        qDebug() << "start event loop";
        QEventLoop loop;
        connect(manager, SIGNAL(finished(qoembed::Response*)), &loop, SLOT(quit()));
        loop.exec();

        resultCache.insert(url, result);
    }

    qDebug() << "done";
    return result;
}

