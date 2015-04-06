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
#ifndef JSONFILE_H
#define JSONFILE_H

#include <QFile>
#include <QJsonDocument>
#include <QTextStream>
#include "jsoncollection.h"
#include "jsontranslator.h"
#include "jsontranslatorfactory.h"

class QString;


template <class T>
class JsonFile
{
public:
    static bool load(const QString &fileName, JsonCollection<T> *collection);
    static bool save(const QString &fileName, JsonCollection<T> *collection);

private:
    JsonFile();
};

template <class T>
bool JsonFile<T>::load(const QString &fileName, JsonCollection<T> *collection)
{
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());

    QScopedPointer<JsonTranslator<T> > translator(JsonTranslatorFactory<T>::create());
    return translator->processDocument(doc,collection);
}

template <class T>
bool JsonFile<T>::save(const QString &fileName, JsonCollection<T> *collection)
{
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QScopedPointer<JsonTranslator<T> > translator(JsonTranslatorFactory<T>::create());
    QJsonDocument doc = translator->createDocument(collection);

    QTextStream out(&jsonFile);
    out << doc.toJson();

    return true;
}

#endif // JSONFILE_H

