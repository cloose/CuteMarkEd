/*
 * Copyright 2014 Christian Loose <christian.loose@hamburg.de>
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
#ifndef JSONTRANSLATOR_H
#define JSONTRANSLATOR_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "jsoncollection.h"

template <class T>
class JsonTranslator
{
public:
    virtual ~JsonTranslator() {}

    bool processDocument(const QJsonDocument &jsonDocument, JsonCollection<T> *collection);
    QJsonDocument createDocument(JsonCollection<T> *collection);

private:
    virtual T fromJsonObject(const QJsonObject &object) = 0;
    virtual QJsonObject toJsonObject(const T &item) = 0;

    virtual bool isValid(const QJsonDocument &jsonDocument, const QString &arrayName) const;
};

template <class T>
bool JsonTranslator<T>::processDocument(const QJsonDocument &jsonDocument, JsonCollection<T> *collection)
{
    if (!isValid(jsonDocument, collection->name()))
        return false;

    QJsonArray array = jsonDocument.object().value(collection->name()).toArray();
    foreach (QJsonValue entry, array) {
        T newItem = fromJsonObject(entry.toObject());
        collection->insert(newItem);
    }

    return true;
}

template <class T>
QJsonDocument JsonTranslator<T>::createDocument(JsonCollection<T> *collection)
{
    QJsonArray array;
    for (int i = 0; i < collection->count(); ++i) {
        T item = collection->at(i);

        QJsonObject entry = toJsonObject(item);
        array.append(entry);
    }

    QJsonObject object;
    object.insert(collection->name(), array);

    QJsonDocument doc(object);
    return doc;
}

template <class T>
bool JsonTranslator<T>::isValid(const QJsonDocument &jsonDocument, const QString &arrayName) const
{
    return !jsonDocument.isEmpty() &&
           jsonDocument.isObject() &&
           jsonDocument.object().contains(arrayName) &&
           jsonDocument.object().value(arrayName).isArray();
}

#endif // JSONTRANSLATOR_H

