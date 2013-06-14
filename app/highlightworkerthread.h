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
#ifndef HIGHLIGHTWORKERTHREAD_H
#define HIGHLIGHTWORKERTHREAD_H

#include <QtCore/qthread.h>
#include <QtCore/qqueue.h>
#include <QtCore/qmutex.h>
#include <QtCore/qwaitcondition.h>

#include "pmh_definitions.h"

class HighlightWorkerThread : public QThread
{
    Q_OBJECT

public:
    explicit HighlightWorkerThread(QObject *parent = 0);

    void enqueue(const QString &text);

signals:
    void resultReady(pmh_element **elements);

protected:
    virtual void run();

private:
    QQueue<QString> tasks;
    QMutex tasksMutex;
    QWaitCondition bufferNotEmpty;
};

#endif // HIGHLIGHTWORKERTHREAD_H
