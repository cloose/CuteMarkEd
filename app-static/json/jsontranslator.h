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

#include <QJsonObject>
#include "jsoncollection.h"
class QJsonDocument;

template <class T>
class JsonTranslator
{
public:
    virtual ~JsonTranslator() {}

    virtual bool processDocument(const QJsonDocument &jsonDocument, JsonCollection<T> *collection) = 0;
    virtual QJsonDocument createDocument(JsonCollection<T> *collection) = 0;
};

#endif // JSONTRANSLATOR_H

