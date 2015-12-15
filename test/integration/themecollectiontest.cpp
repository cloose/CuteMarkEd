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

void ThemeCollectionTest::initTestCase()
{
    themeFile = new QTemporaryFile(this);
    if (!themeFile->open())
        QFAIL("Failed to create temporary theme file");

    QTextStream out(themeFile);
    out << "{ \"themes\": ["
        << "   {  \"name\": \"default\","
        << "      \"markdownHighlighting\": \"default\","
        << "      \"codeHighlighting\": \"default\","
        << "      \"previewStylesheet\": \"default\" },"
        << "   {  \"name\": \"dark\","
        << "      \"markdownHighlighting\": \"dark\","
        << "      \"codeHighlighting\": \"black\","
        << "      \"previewStylesheet\": \"dark\" } ] }";
}

void ThemeCollectionTest::cleanupTestCase()
{
    themeFile->close();
}

void ThemeCollectionTest::loadsThemesFromFileIntoCollection()
{
    ThemeCollection themeCollection;

    themeCollection.load(themeFile->fileName());

    QStringList themeNames = themeCollection.themeNames();
    QCOMPARE(themeNames.count(), 2);
    QCOMPARE(themeNames.at(0), QLatin1String("default"));
    QCOMPARE(themeNames.at(1), QLatin1String("dark"));
}
