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
#include "jsonthemefiletest.h"


#include <QtTest>
#include <QTemporaryFile>
#include <QTextStream>

#include <jsonfile.h>
#include <themes/jsonthemetranslatorfactory.h>
#include <themes/themecollection.h>


void JsonThemeFileTest::loadsEmptyThemeCollectionFromFile()
{
    QTemporaryFile themeFile(this);
    if (!themeFile.open())
        QFAIL("Failed to create temporary theme file");

    QTextStream out(&themeFile); out << "{ \"themes\": [] }";

    themeFile.close();

    ThemeCollection collection;
    bool success = JsonFile<Theme>::load(themeFile.fileName(), &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 0);
}

void JsonThemeFileTest::loadsThemesCollectionFromFile()
{
    QTemporaryFile themeFile(this);
    if (!themeFile.open())
        QFAIL("Failed to create temporary theme file");

    QTextStream out(&themeFile);
    out << "{ \"themes\": ["
        << "   {  \"name\": \"default\","
        << "      \"markdownHighlighting\": \"default\","
        << "      \"codeHighlighting\": \"default\","
        << "      \"previewStylesheet\": \"default\","
        << "      \"builtIn\": true },"
        << "   {  \"name\": \"dark\","
        << "      \"markdownHighlighting\": \"dark\","
        << "      \"codeHighlighting\": \"black\","
        << "      \"previewStylesheet\": \"dark\" } ] }";

    themeFile.close();

    ThemeCollection collection;
    bool success = JsonFile<Theme>::load(themeFile.fileName(), &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 2);
    QCOMPARE(collection.at(0).name(), QLatin1String("default"));
    QCOMPARE(collection.at(1).name(), QLatin1String("dark"));
}

void JsonThemeFileTest::savesEmptyThemesCollectionToFile()
{
    QTemporaryFile themeFile(this);
    if (!themeFile.open())
        QFAIL("Failed to create temporary theme file");

    ThemeCollection collection;
    bool success = JsonFile<Theme>::save(themeFile.fileName(), &collection);

    QVERIFY(success);

    QTextStream in(&themeFile);
    QString fileContent = in.readAll().trimmed();

    QVERIFY(fileContent.startsWith("{"));
    QVERIFY(fileContent.contains("\"themes\": ["));
    QVERIFY(fileContent.endsWith("}"));
}

void JsonThemeFileTest::savesThemesCollectionToFile()
{
    QTemporaryFile themeFile(this);
    if (!themeFile.open())
        QFAIL("Failed to create temporary theme file");

    Theme theme1("default", "default", "default", "default");

    Theme theme2("dark", "dark", "black", "dark");

    ThemeCollection collection;
    collection.insert(theme1);
    collection.insert(theme2);

    bool success = JsonFile<Theme>::save(themeFile.fileName(), &collection);

    QVERIFY(success);

    QTextStream in(&themeFile);
    QString fileContent = in.readAll().trimmed();

    QVERIFY(fileContent.startsWith("{"));
    QVERIFY(fileContent.contains("\"themes\": ["));
    QVERIFY(fileContent.contains("\"name\": \"default\""));
    QVERIFY(fileContent.contains("\"name\": \"dark\""));
    QVERIFY(fileContent.endsWith("}"));
}

void JsonThemeFileTest::roundtripTest()
{
    QTemporaryFile themeFile(this);
    if (!themeFile.open())
        QFAIL("Failed to create temporary theme file");

    Theme theme1("default", "default", "default", "default", true);

    Theme theme2("dark", "dark", "black", "dark");

    ThemeCollection collection1;
    collection1.insert(theme1);
    collection1.insert(theme2);

    bool saveSuccess = JsonFile<Theme>::save(themeFile.fileName(), &collection1);
    QVERIFY(saveSuccess);

    ThemeCollection collection2;
    bool loadSuccess = JsonFile<Theme>::load(themeFile.fileName(), &collection2);
    QVERIFY(loadSuccess);

    QCOMPARE(collection2.count(), 2);

    QCOMPARE(collection2.at(0).name(), theme1.name());
    QCOMPARE(collection2.at(0).markdownHighlighting(), theme1.markdownHighlighting());
    QCOMPARE(collection2.at(0).codeHighlighting(), theme1.codeHighlighting());
    QCOMPARE(collection2.at(0).previewStylesheet(), theme1.previewStylesheet());
    QCOMPARE(collection2.at(0).isBuiltIn(), theme1.isBuiltIn());

    QCOMPARE(collection2.at(1).name(), theme2.name());
    QCOMPARE(collection2.at(1).markdownHighlighting(), theme2.markdownHighlighting());
    QCOMPARE(collection2.at(1).codeHighlighting(), theme2.codeHighlighting());
    QCOMPARE(collection2.at(1).previewStylesheet(), theme2.previewStylesheet());
    QCOMPARE(collection2.at(0).isBuiltIn(), theme1.isBuiltIn());
}
