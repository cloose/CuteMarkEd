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

void ThemeCollectionTest::returnsIfCollectionContainsTheme()
{
    ThemeCollection collection;
    Theme theme("name", "markdown", "code", "preview");
    collection.insert(theme);
    
    QCOMPARE(collection.contains("name"), true);
    QCOMPARE(collection.contains("missing"), false);
}

void ThemeCollectionTest::returnsThemeByName()
{
    ThemeCollection collection;
    Theme theme("name", "markdown", "code", "preview");
    collection.insert(theme);
    
    Theme actual = collection.theme("name");

    QCOMPARE(actual, theme);
}

void ThemeCollectionTest::returnsNameOfAllThemes()
{
    Theme theme1("name 1", "markdown", "code", "preview");
    Theme theme2("name 2", "markdown", "code", "preview");
    ThemeCollection collection;
    collection.insert(theme1);
    collection.insert(theme2);
    
    QStringList themeNames = collection.themeNames();

    QCOMPARE(themeNames.count(), 2);
    QCOMPARE(themeNames.at(0), theme1.name());
    QCOMPARE(themeNames.at(1), theme2.name());
}

