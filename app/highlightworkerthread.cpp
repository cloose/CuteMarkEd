#include "highlightworkerthread.h"

#include "pmh_parser.h"

HighlightWorkerThread::HighlightWorkerThread(QObject *parent) :
    QThread(parent)
{
}


void HighlightWorkerThread::enqueue(const QString &text)
{
    QMutexLocker locker(&tasksMutex);
    tasks.enqueue(text);
    bufferNotEmpty.wakeOne();
}


void HighlightWorkerThread::run()
{
    forever {
        QString text;

        {
            // wait for new task
            QMutexLocker locker(&tasksMutex);
            while (tasks.count() == 0) {
                bufferNotEmpty.wait(&tasksMutex);
            }

            // get next task from queue
            text = tasks.dequeue();
        }

        // end processing?
        if (text.isNull()) {
            return;
        }

        // parse markdown and generate syntax elements
        pmh_element **elements;
        pmh_markdown_to_elements(text.toUtf8().data(), pmh_EXT_NONE, &elements);

        emit resultReady(elements);
    }
}
