#ifndef HTMLPREVIEWGENERATOR_H
#define HTMLPREVIEWGENERATOR_H

#include <QtCore/qthread.h>
#include <QtCore/qqueue.h>
#include <QtCore/qmutex.h>
#include <QtCore/qwaitcondition.h>

class HtmlPreviewGenerator : public QThread
{
    Q_OBJECT

public:
    explicit HtmlPreviewGenerator(QObject *parent = 0);
    
    void enqueue(const QString &text);

signals:
    void resultReady(const QString &html);
    
protected:
    virtual void run();

private:
    QQueue<QString> tasks;
    QMutex tasksMutex;
    QWaitCondition bufferNotEmpty;
};

#endif // HTMLPREVIEWGENERATOR_H
