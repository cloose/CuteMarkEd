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
#include "thememanagertest.h"

#include <QtTest>

#include <themes/thememanager.h>

void ThemeManagerTest::initTestCase()
{
    QTemporaryFile themeFile(this);
    if (!themeFile.open())
        QFAIL("Failed to create temporary theme file");

    QTextStream out(&themeFile);
    out << "{ \"themes\": ["
        << "   {  \"name\": \"default\","
        << "      \"markdownHighlighting\": \"default\","
        << "      \"codeHighlighting\": \"default\","
        << "      \"previewStylesheet\": \"default\" },"
        << "   {  \"name\": \"dark\","
        << "      \"markdownHighlighting\": \"dark\","
        << "      \"codeHighlighting\": \"black\","
        << "      \"previewStylesheet\": \"dark\" } ] }";

    themeFile.close();

    themeManager = new ThemeManager(themeFile.fileName());
}

void ThemeManagerTest::cleanupTestCase()
{
    delete themeManager;
}

void ThemeManagerTest::returnsBuiltinThemeByName()
{
    Theme actual = themeManager->themeByName("dark");

    QCOMPARE(actual.name(), QLatin1String("dark"));
    QCOMPARE(actual.markdownHighlighting(), QLatin1String("dark"));
    QCOMPARE(actual.codeHighlighting(), QLatin1String("black"));
    QCOMPARE(actual.previewStylesheet(), QLatin1String("dark"));
}

void ThemeManagerTest::returnsNameOfAllBuiltinThemes()
{
    QStringList themeNames = themeManager->themeNames();

    QCOMPARE(themeNames.count(), 2);
    QCOMPARE(themeNames.at(0), QLatin1String("default"));
    QCOMPARE(themeNames.at(1), QLatin1String("dark"));
}

