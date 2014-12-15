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
#include "stylecollectiontest.h"

#include <QtTest>

#include <styles/stylecollection.h>


void StyleCollectionTest::initTestCase()
{
}

void StyleCollectionTest::holdsStylesInInserationOrder()
{
    Style style1; style1.name = "a";
    Style style2; style2.name = "b";
    Style style3; style3.name = "c";

    StyleCollection collection;

    collection.insert(style2);    // b
    collection.insert(style3);    // c
    collection.insert(style1);    // a

    QCOMPARE(collection.styleNames().at(0), style2.name);    // b
    QCOMPARE(collection.styleNames().at(1), style3.name);    // c
    QCOMPARE(collection.styleNames().at(2), style1.name);    // a
}

void StyleCollectionTest::canRetrieveStyleByName()
{
    Style style; style.name = "ArbitraryName";
    StyleCollection collection;

    collection.insert(style);

    QCOMPARE(collection.style("ArbitraryName").name, style.name);
}

void StyleCollectionTest::canCheckIfContainsStyleByName()
{
    Style style; style.name = "ArbitraryName";
    StyleCollection collection;

    collection.insert(style);

    QCOMPARE(collection.contains("ArbitraryName"), true);
    QCOMPARE(collection.contains("NonExistingName"), false);
}
