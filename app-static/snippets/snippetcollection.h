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
#ifndef SNIPPETCOLLECTION_H
#define SNIPPETCOLLECTION_H

#include <QObject>
#include <QMap>
#include "snippet.h"


class SnippetCollection : public QObject
{
    Q_OBJECT
    Q_ENUMS(CollectionChangedType)

public:
    enum CollectionChangedType
    {
        ItemAdded,
        ItemChanged,
        ItemDeleted
    };

    explicit SnippetCollection(QObject *parent = 0);

    int count() const;

    int insert(const Snippet& snippet);
    void update(const Snippet& snippet);
    void remove(const Snippet& snippet);

    bool contains(const QString &trigger) const;
    const Snippet snippet(const QString &trigger) const;
    const Snippet &snippetAt(int offset) const;

    QSharedPointer<SnippetCollection> userDefinedSnippets() const;

signals:
    void collectionChanged(SnippetCollection::CollectionChangedType changedType, const Snippet &snippet);

private:
    QMap<QString, Snippet> snippets;
};

#endif // SNIPPETCOLLECTION_H
