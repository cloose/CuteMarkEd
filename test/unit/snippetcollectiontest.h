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
#ifndef SNIPPETCOLLECTIONTEST_H
#define SNIPPETCOLLECTIONTEST_H

#include <QObject>
#include <snippets/snippetcollection.h>


class SnippetCollectionTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void notifiesListenersOfNewSnippets();
    void notifiesListenersOfChangedSnippets();
    void notifiesListenersOfRemovedSnippets();

    void holdsSnippetsInTriggerOrder();

    void returnsNewCollectionOfUserDefinedSnippets();
};

Q_DECLARE_METATYPE(SnippetCollection::CollectionChangedType) // for QSignalSpy
Q_DECLARE_METATYPE(Snippet) // for QSignalSpy

#endif // SNIPPETCOLLECTIONTEST_H
