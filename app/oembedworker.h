#ifndef OEMBEDWORKER_H
#define OEMBEDWORKER_H

#include <QObject>

#include <QMap>

namespace qoembed {
class OEmbedManager;
class Response;
}

class OEmbedWorker : public QObject
{
    Q_OBJECT
public:
    explicit OEmbedWorker(qoembed::OEmbedManager *mgr, QObject *parent = 0);
    ~OEmbedWorker();
    
public slots:
    QString doWork(const QString &url);

private slots:
    void finished(qoembed::Response *response);

private:
    qoembed::OEmbedManager *manager;
    QString result;
    QMap<QString, QString> resultCache;
};

#endif // OEMBEDWORKER_H
