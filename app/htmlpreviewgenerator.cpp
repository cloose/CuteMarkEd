#include "htmlpreviewgenerator.h"

#include "discount/document.h"

HtmlPreviewGenerator::HtmlPreviewGenerator(QObject *parent) :
    QThread(parent)
{
}

void HtmlPreviewGenerator::enqueue(const QString &text)
{
    QMutexLocker locker(&tasksMutex);
    tasks.enqueue(text);
    bufferNotEmpty.wakeOne();
}

void HtmlPreviewGenerator::setHtmlTemplate(const QString &t)
{
    htmlTemplate = t;
}


void HtmlPreviewGenerator::run()
{
    forever {
        QString text;

        {
            // wait for new task
            QMutexLocker locker(&tasksMutex);
            while (tasks.count() == 0) {
                bufferNotEmpty.wait(&tasksMutex);
            }

            text = tasks.dequeue();
        }

        // end processing?
        if (text.isNull()) {
            return;
        }

        // generate HTML from markdown
        Discount::Document document(text);
        QString htmlContent = document.toHtml();
        QString html = renderTemplate(htmlContent);
        emit htmlResultReady(html);

        // generate table of contents
        QString toc = document.generateToc();
        emit tocResultReady(toc);
    }
}

QString HtmlPreviewGenerator::renderTemplate(const QString &content)
{
    if (htmlTemplate.isEmpty()) {
        return content;
    }

    return QString(htmlTemplate).replace(QLatin1String("__HTML_CONTENT__"), content);
}
