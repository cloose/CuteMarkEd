/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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

            // get last task from queue and skip all previous tasks
            while (!tasks.isEmpty())
                text = tasks.dequeue();
        }

        // end processing?
        if (text.isNull()) {
            return;
        }

        // delay processing by 500 ms to see if more tasks are coming
        // (e.g. because the user is typing fast)
        this->msleep(500);

        // no more new tasks?
        if (tasks.isEmpty()) {
            // parse markdown and generate syntax elements
            pmh_element **elements;
            pmh_markdown_to_elements(text.toUtf8().data(), pmh_EXT_NONE, &elements);

            emit resultReady(elements);
        }
    }
}
