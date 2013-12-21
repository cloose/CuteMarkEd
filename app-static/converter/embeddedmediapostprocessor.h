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
#ifndef EMBEDDEDMEDIAPOSTPROCESSOR_H
#define EMBEDDEDMEDIAPOSTPROCESSOR_H

#include <QObject>
#include <converter/htmlpostprocessor.h>

#include <QMap>
#include <QRegularExpression>

namespace qoembed {
class OEmbedManager;
class Response;
}

class EmbeddedMediaPostprocessor : public QObject, public HtmlPostprocessor
{
    Q_OBJECT

public:
    explicit EmbeddedMediaPostprocessor(QObject *parent = 0);
    virtual ~EmbeddedMediaPostprocessor();

protected:
    virtual void doProcessHtml(QString &html);

private slots:
    void finished(qoembed::Response *response);

private:
    QString fetchResourceFromUrl(const QString &url);

    qoembed::OEmbedManager *manager;
    QString result;
    QMap<QString, QString> resultCache;

    static QRegularExpression re;
};

#endif // EMBEDDEDMEDIAPOSTPROCESSOR_H
