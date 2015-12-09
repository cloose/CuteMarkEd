/*
 * Copyright 2015 Christian Loose <christian.loose@hamburg.de>
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
#include "themecollectiontest.h"

#include <QtTest>

#include <themes/themecollection.h>


void ThemeCollectionTest::returnsConstantNameOfJsonArray()
{
    ThemeCollection collection;
    QCOMPARE(collection.name(), QStringLiteral("themes"));
}

void ThemeCollectionTest::returnsNumberOfThemesInCollection()
{
    ThemeCollection collection;
    Theme theme("name", "markdown", "code", "preview");
    collection.insert(theme);

    QCOMPARE(collection.count(), 1);
}

void ThemeCollectionTest::returnsThemeAtIndexPosition()
{
    ThemeCollection collection;
    Theme theme("name", "markdown", "code", "preview");
    collection.insert(theme);

    Theme actual = collection.at(0);

    QCOMPARE(actual, theme);
}

