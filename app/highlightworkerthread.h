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
