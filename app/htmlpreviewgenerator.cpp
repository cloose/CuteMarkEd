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
        QString html = document.toHtml();

        emit resultReady(html);
    }
}
