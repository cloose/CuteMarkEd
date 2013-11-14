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
#include "snippetrepository.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>

#include "snippet.h"
#include <QTextStream>


SnippetRepository::SnippetRepository(QObject *parent) :
    QObject(parent),
    longestTrigger(0)
{
}

void SnippetRepository::loadFromFile(const QString &fileName)
{
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());

    QJsonArray snippetArray = doc.object().value("snippets").toArray();
    foreach (QJsonValue entry, snippetArray) {
        Snippet snippet = Snippet::fromJsonObject(entry.toObject());
        addSnippet(snippet);

        longestTrigger = qMax(longestTrigger, snippet.trigger.length());
    }

    emit dataChanged();
}

void SnippetRepository::saveToFile(const QString &fileName)
{
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QJsonArray snippetArray;
    foreach (Snippet snippet, snippets.values()) {
        if (!snippet.builtIn) {
            QJsonObject entry = Snippet::toJsonObject(snippet);
            snippetArray.append(entry);
        }
    }

    QJsonObject object;
    object.insert("snippets", snippetArray);

    QJsonDocument doc(object);

    QTextStream out(&jsonFile);
    out << doc.toJson();
}

void SnippetRepository::clear()
{
    snippets.clear();
}

int SnippetRepository::addSnippet(Snippet snippet)
{
    QMap<QString, Snippet>::iterator it = snippets.insert(snippet.trigger, snippet);
    longestTrigger = qMax(longestTrigger, snippet.trigger.length());
    emit dataChanged();
    return std::distance(snippets.begin(), it);
}

void SnippetRepository::removeSnippet(Snippet snippet)
{
    snippets.remove(snippet.trigger);
    emit dataChanged();
}

void SnippetRepository::setSnippetContent(const Snippet &snippet, const QString &content)
{
    Snippet &s = snippets[snippet.trigger];
    s.setContent(content);
}

bool SnippetRepository::contains(const QString &trigger) const
{
    return snippets.contains(trigger);
}

Snippet SnippetRepository::snippet(const QString &trigger) const
{
    return snippets[trigger];
}

int SnippetRepository::count() const
{
    return snippets.count();
}

QList<Snippet> SnippetRepository::values() const
{
    return snippets.values();
}

int SnippetRepository::maxTriggerLength() const
{
    return longestTrigger;
}
