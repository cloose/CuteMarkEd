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

    snippets.clear();

    QJsonArray snippetArray = doc.object().value("snippets").toArray();
    foreach (QJsonValue entry, snippetArray) {
        Snippet snippet = Snippet::fromJsonObject(entry.toObject());
        addSnippet(snippet);

        longestTrigger = qMax(longestTrigger, snippet.trigger.length());
    }

    emit dataChanged();
}

void SnippetRepository::addSnippet(Snippet snippet)
{
    snippets.insert(snippet.trigger, snippet);
}

void SnippetRepository::removeSnippet(Snippet snippet)
{
    snippets.remove(snippet.trigger);
}

bool SnippetRepository::contains(const QString &trigger) const
{
    return snippets.contains(trigger);
}

Snippet SnippetRepository::snippet(const QString &trigger) const
{
    return snippets[trigger];
}

QList<Snippet> SnippetRepository::values() const
{
    return snippets.values();
}

int SnippetRepository::maxTriggerLength() const
{
    return longestTrigger;
}
