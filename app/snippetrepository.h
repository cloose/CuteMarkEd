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
#ifndef SNIPPETREPOSITORY_H
#define SNIPPETREPOSITORY_H

#include <QObject>
#include <QMap>

#include <snippets/snippet.h>


class SnippetRepository : public QObject
{
    Q_OBJECT
public:
    explicit SnippetRepository(QObject *parent = 0);
    
    void loadFromFile(const QString &fileName);
    void saveToFile(const QString &fileName);

    void clear();
    int addSnippet(Snippet snippet);
    void removeSnippet(Snippet snippet);
    void setSnippetContent(const Snippet &snippet, const QString &content);

    bool contains(const QString &trigger) const;
    Snippet snippet(const QString &trigger) const;

    int count() const;
    QList<Snippet> values() const;

    int maxTriggerLength() const;

signals:
    void dataChanged();

private:
    QMap<QString, Snippet> snippets;
    int longestTrigger;
};

#endif // SNIPPETREPOSITORY_H
