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
    void setHtmlTemplate(const QString &t);

signals:
    void resultReady(const QString &html);
    
protected:
    virtual void run();

private:
    QString renderTemplate(const QString &content);

private:
    QQueue<QString> tasks;
    QMutex tasksMutex;
    QWaitCondition bufferNotEmpty;
    QString htmlTemplate;
};

#endif // HTMLPREVIEWGENERATOR_H
