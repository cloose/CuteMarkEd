#include "oembedworker.h"

#include <QDebug>

#include <oembedmanager.h>
#include <request.h>
#include <response.h>
#include <QEventLoop>
using qoembed::OEmbedManager;
using qoembed::Request;
using qoembed::Response;

OEmbedWorker::OEmbedWorker(OEmbedManager *mgr, QObject *parent) :
    QObject(parent),
    manager(mgr)
{
    qDebug() << "connect to finished signal of OEmbedManager";
    connect(manager, SIGNAL(finished(qoembed::Response*)),
            SLOT(finished(qoembed::Response*)));
}

OEmbedWorker::~OEmbedWorker()
{
    qDebug() << "OembedWorker destructor";
}

QString OEmbedWorker::doWork(const QString &url)
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

void OEmbedWorker::finished(qoembed::Response *response)
{
    result = response->render();
}
