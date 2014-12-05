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
#include "jsonstylefiletest.h"

#include <QtTest>
#include <QTemporaryFile>
#include <QTextStream>

#include <jsonfile.h>
#include <styles/stylecollection.h>

void JsonStyleFileTest::loadsEmptyStylesCollectionFromFile()
{
    QTemporaryFile styleFile(this);
    if (!styleFile.open())
        QFAIL("Failed to create temporary style file");

    QTextStream out(&styleFile); out << "{ \"styles\": [] }";

    styleFile.close();

    StyleCollection collection;
    bool success = JsonFile<Style>::load(styleFile.fileName(), &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 0);
}

void JsonStyleFileTest::loadsStylesCollectionFromFile()
{
    QTemporaryFile styleFile(this);
    if (!styleFile.open())
        QFAIL("Failed to create temporary style file");

    QTextStream out(&styleFile);
    out << "{ \"styles\": ["
        << "   {  \"name\": \"abc\","
        << "      \"markdownHighlighting\": \"markdownHighlighting abc\","
        << "      \"codeHighlighting\": \"codeHighlighting abc\","
        << "      \"previewStylesheet\": \"previewStylesheet abc\","
        << "      \"builtIn\": true },"
        << "   {  \"name\": \"xyz\","
        << "      \"markdownHighlighting\": \"markdownHighlighting xyz\","
        << "      \"codeHighlighting\": \"codeHighlighting xyz\","
        << "      \"previewStylesheet\": \"previewStylesheet xyz\","
        << "      \"builtIn\": false } ] }";

    styleFile.close();

    StyleCollection collection;
    bool success = JsonFile<Style>::load(styleFile.fileName(), &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 2);
    QVERIFY(collection.contains("abc"));
    QVERIFY(collection.contains("xyz"));
}

void JsonStyleFileTest::savesEmptyStylesCollectionToFile()
{
    QTemporaryFile styleFile(this);
    if (!styleFile.open())
        QFAIL("Failed to create temporary style file");

    StyleCollection collection;
    bool success = JsonFile<Style>::save(styleFile.fileName(), &collection);

    QVERIFY(success);

    QTextStream in(&styleFile);
    QString fileContent = in.readAll().trimmed();

    QVERIFY(fileContent.startsWith("{"));
    QVERIFY(fileContent.contains("\"styles\": ["));
    QVERIFY(fileContent.endsWith("}"));
}

void JsonStyleFileTest::savesStylesCollectionToFile()
{
    QTemporaryFile styleFile(this);
    if (!styleFile.open())
        QFAIL("Failed to create temporary style file");

    Style style1;
    style1.name = "abc";

    Style style2;
    style2.name = "xyz";

    StyleCollection collection;
    collection.insert(style1);
    collection.insert(style2);

    bool success = JsonFile<Style>::save(styleFile.fileName(), &collection);

    QVERIFY(success);

    QTextStream in(&styleFile);
    QString fileContent = in.readAll().trimmed();

    QVERIFY(fileContent.startsWith("{"));
    QVERIFY(fileContent.contains("\"styles\": ["));
    QVERIFY(fileContent.contains("\"name\": \"abc\""));
    QVERIFY(fileContent.contains("\"name\": \"xyz\""));
    QVERIFY(fileContent.endsWith("}"));
}

void JsonStyleFileTest::roundtripTest()
{
    QTemporaryFile styleFile(this);
    if (!styleFile.open())
        QFAIL("Failed to create temporary style file");

    Style style1;
    style1.name = "abc";
    style1.markdownHighlighting = "markdownHighlighting abc";
    style1.codeHighlighting = "codeHighlighting abc";
    style1.previewStylesheet = "previewStylesheet abc";
    style1.builtIn = true;

    Style style2;
    style2.name = "xyz";
    style2.markdownHighlighting = "markdownHighlighting xyz";
    style2.codeHighlighting = "codeHighlighting xyz";
    style2.previewStylesheet = "previewStylesheet xyz";
    style2.builtIn = false;

    StyleCollection collection1;
    collection1.insert(style1);
    collection1.insert(style2);

    bool saveSuccess = JsonFile<Style>::save(styleFile.fileName(), &collection1);
    QVERIFY(saveSuccess);

    StyleCollection collection2;
    bool loadSuccess = JsonFile<Style>::load(styleFile.fileName(), &collection2);
    QVERIFY(loadSuccess);

    QCOMPARE(collection2.count(), 2);

    QCOMPARE(collection2.style("abc").markdownHighlighting, style1.markdownHighlighting);
    QCOMPARE(collection2.style("abc").codeHighlighting, style1.codeHighlighting);
    QCOMPARE(collection2.style("abc").previewStylesheet, style1.previewStylesheet);
    QCOMPARE(collection2.style("abc").builtIn, style1.builtIn);

    QCOMPARE(collection2.style("xyz").markdownHighlighting, style2.markdownHighlighting);
    QCOMPARE(collection2.style("xyz").codeHighlighting, style2.codeHighlighting);
    QCOMPARE(collection2.style("xyz").previewStylesheet, style2.previewStylesheet);
    QCOMPARE(collection2.style("xyz").builtIn, style2.builtIn);
}

