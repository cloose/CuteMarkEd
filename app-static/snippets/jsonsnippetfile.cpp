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
#include "jsonsnippetfile.h"

#include <QFile>
#include <QJsonDocument>
#include <QTextStream>

#include "jsonsnippettranslator.h"
#include "snippetcollection.h"


bool JsonSnippetFile::load(const QString &fileName, SnippetCollection *collection)
{
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());

    JsonSnippetTranslator translator;
    return translator.processDocument(doc, collection);
}

bool JsonSnippetFile::save(const QString &fileName, SnippetCollection *collection)
{
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    JsonSnippetTranslator translator;
    QJsonDocument doc = translator.createDocument(collection);

    QTextStream out(&jsonFile);
    out << doc.toJson();

    return true;
}
