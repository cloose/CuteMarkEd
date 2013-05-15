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
    void setMathSupportEnabled(bool enabled);

signals:
    void htmlResultReady(const QString &html);
    void tocResultReady(const QString &toc);

protected:
    virtual void run();

private:
    QString renderTemplate(const QString &header, const QString &content);
    QString buildHtmlHeader() const;

private:
    QQueue<QString> tasks;
    QMutex tasksMutex;
    QWaitCondition bufferNotEmpty;
    QString htmlTemplate;
    bool mathSupportEnabled;
};

#endif // HTMLPREVIEWGENERATOR_H
