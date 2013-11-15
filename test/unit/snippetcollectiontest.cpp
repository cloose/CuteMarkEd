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
#include "snippetcollectiontest.h"

#include <QtTest>

#include <snippets/snippetcollection.h>


void SnippetCollectionTest::initTestCase()
{
    collection = new SnippetCollection(this);
}

void SnippetCollectionTest::notifiesListenersOfNewSnippets()
{
    qRegisterMetaType<CollectionChangedType>();  // for QSignalSpy

    const Snippet snippet;
    QSignalSpy spy(collection, SIGNAL(collectionChanged(CollectionChangedType)));

    collection->insert(snippet);

    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();

//    QCOMPARE((SnippetCollection::CollectionChangedType)arguments.at(0).toInt(), SnippetCollection::ItemAdded);
    QCOMPARE(arguments.at(0).value<SnippetCollection::CollectionChangedType>(), SnippetCollection::ItemAdded);
}

void SnippetCollectionTest::cleanupTestCase()
{
    delete collection;
}
