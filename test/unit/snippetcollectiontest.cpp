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
    qRegisterMetaType<SnippetCollection::CollectionChangedType>();  // for QSignalSpy
    qRegisterMetaType<Snippet>();  // for QSignalSpy
}

void SnippetCollectionTest::notifiesListenersOfNewSnippets()
{
    const Snippet snippet;
    SnippetCollection collection;

    QSignalSpy spy(&collection, SIGNAL(collectionChanged(SnippetCollection::CollectionChangedType, Snippet)));

    collection.insert(snippet);

    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).value<SnippetCollection::CollectionChangedType>(), SnippetCollection::ItemAdded);
}

void SnippetCollectionTest::notifiesListenersOfChangedSnippets()
{
    const Snippet snippet;
    SnippetCollection collection;
    QSignalSpy spy(&collection, SIGNAL(collectionChanged(SnippetCollection::CollectionChangedType, Snippet)));

    collection.insert(snippet);
    collection.update(snippet);

    QCOMPARE(spy.count(), 2);

    QList<QVariant> arguments = spy.takeAt(1);
    QCOMPARE(arguments.at(0).value<SnippetCollection::CollectionChangedType>(), SnippetCollection::ItemChanged);
}

void SnippetCollectionTest::notifiesListenersOfRemovedSnippets()
{
    const Snippet snippet;
    SnippetCollection collection;
    QSignalSpy spy(&collection, SIGNAL(collectionChanged(SnippetCollection::CollectionChangedType, Snippet)));

    collection.insert(snippet);
    collection.remove(snippet);

    QCOMPARE(spy.count(), 2);

    QList<QVariant> arguments = spy.takeAt(1);
    QCOMPARE(arguments.at(0).value<SnippetCollection::CollectionChangedType>(), SnippetCollection::ItemDeleted);
}

void SnippetCollectionTest::holdsSnippetsInTriggerOrder()
{
    Snippet snippet1; snippet1.trigger = "a";
    Snippet snippet2; snippet2.trigger = "b";
    Snippet snippet3; snippet3.trigger = "c";

    SnippetCollection collection;

    collection.insert(snippet2);    // b
    collection.insert(snippet3);    // c
    collection.insert(snippet1);    // a

    QCOMPARE(collection.at(0).trigger, snippet1.trigger);    // a
    QCOMPARE(collection.at(1).trigger, snippet2.trigger);    // b
    QCOMPARE(collection.at(2).trigger, snippet3.trigger);    // c
}

void SnippetCollectionTest::returnsNewCollectionOfUserDefinedSnippets()
{
    Snippet snippet1; snippet1.trigger = "a"; snippet1.builtIn = true;
    Snippet snippet2; snippet2.trigger = "b"; snippet2.builtIn = false;
    Snippet snippet3; snippet3.trigger = "c"; snippet3.builtIn = false;

    SnippetCollection collection;
    collection.insert(snippet2);
    collection.insert(snippet1);
    collection.insert(snippet3);

    QSharedPointer<SnippetCollection> userDefinedSnippets = collection.userDefinedSnippets();

    QVERIFY(!userDefinedSnippets.isNull());
    QVERIFY(userDefinedSnippets.data() != &collection);
    QCOMPARE(userDefinedSnippets->count(), 2);
    QVERIFY(!userDefinedSnippets->contains(snippet1.trigger));
    QVERIFY(userDefinedSnippets->contains(snippet2.trigger));
    QVERIFY(userDefinedSnippets->contains(snippet3.trigger));
}

void SnippetCollectionTest::returnsConstantNameOfJsonArray()
{
    SnippetCollection collection;
    QCOMPARE(collection.name(), QStringLiteral("snippets"));
}

void SnippetCollectionTest::returnsEmptySnippetForNonExistingTrigger()
{
    Snippet snippet; snippet.trigger = "ArbitraryName";
    SnippetCollection collection;
    collection.insert(snippet);

    Snippet foundSnippet = collection.snippet("NonExistingSnippet");

    QCOMPARE(foundSnippet.trigger, QString());
    QCOMPARE(foundSnippet.description, QString());
    QCOMPARE(foundSnippet.snippet, QString());
}
