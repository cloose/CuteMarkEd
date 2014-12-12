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
#ifndef JSONSNIPPETTRANSLATOR_H
#define JSONSNIPPETTRANSLATOR_H

#include "json/jsontranslator.h"
#include <QJsonObject>
class QJsonDocument;
class SnippetCollection;
struct Snippet;


class JsonSnippetTranslator : public JsonTranslator<Snippet>
{
public:
    bool processDocument(const QJsonDocument &jsonDocument, JsonCollection<Snippet> *collection) Q_DECL_OVERRIDE;
    QJsonDocument createDocument(JsonCollection<Snippet> *collection) Q_DECL_OVERRIDE;

private:
    Snippet fromJsonObject(const QJsonObject &object);
    QJsonObject toJsonObject(const Snippet &snippet);

    bool isValid(const QJsonDocument &jsonDocument) const;
};

#endif // JSONSNIPPETTRANSLATOR_H
