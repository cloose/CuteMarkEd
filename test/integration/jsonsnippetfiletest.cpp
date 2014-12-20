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
#include "jsonsnippetfiletest.h"

#include <QtTest>
#include <QTemporaryFile>
#include <QTextStream>

#include <jsonfile.h>
#include <snippets/jsonsnippettranslatorfactory.h>
#include <snippets/snippetcollection.h>

void JsonSnippetFileTest::loadsEmptySnippetsCollectionFromFile()
{
    QTemporaryFile snippetFile(this);
    if (!snippetFile.open())
        QFAIL("Failed to create temporary snippet file");

    QTextStream out(&snippetFile); out << "{ \"snippets\": [] }";

    snippetFile.close();

    SnippetCollection collection;
    bool success = JsonFile<Snippet>::load(snippetFile.fileName(), &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 0);
}

void JsonSnippetFileTest::loadsSnippetsCollectionFromFile()
{
    QTemporaryFile snippetFile(this);
    if (!snippetFile.open())
        QFAIL("Failed to create temporary snippet file");

    QTextStream out(&snippetFile);
    out << "{ \"snippets\": ["
        << "   {  \"trigger\": \"abc\","
        << "      \"description\": \"description xyz\","
        << "      \"snippet\": \"content abc\","
        << "      \"cursor\": 0,"
        << "      \"builtIn\": true },"
        << "   {  \"trigger\": \"xyz\","
        << "      \"description\": \"description xyz\","
        << "      \"snippet\": \"content xyz\","
        << "      \"cursor\": 1,"
        << "      \"builtIn\": false } ] }";

    snippetFile.close();

    SnippetCollection collection;
    bool success = JsonFile<Snippet>::load(snippetFile.fileName(), &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 2);
    QVERIFY(collection.contains("abc"));
    QVERIFY(collection.contains("xyz"));
}

void JsonSnippetFileTest::savesEmptySnippetsCollectionToFile()
{
    QTemporaryFile snippetFile(this);
    if (!snippetFile.open())
        QFAIL("Failed to create temporary snippet file");

    SnippetCollection collection;
    bool success = JsonFile<Snippet>::save(snippetFile.fileName(), &collection);

    QVERIFY(success);

    QTextStream in(&snippetFile);
    QString fileContent = in.readAll().trimmed();

    QVERIFY(fileContent.startsWith("{"));
    QVERIFY(fileContent.contains("\"snippets\": ["));
    QVERIFY(fileContent.endsWith("}"));
}

void JsonSnippetFileTest::savesSnippetsCollectionToFile()
{
    QTemporaryFile snippetFile(this);
    if (!snippetFile.open())
        QFAIL("Failed to create temporary snippet file");

    Snippet snippet1;
    snippet1.trigger = "abc";

    Snippet snippet2;
    snippet2.trigger = "xyz";

    SnippetCollection collection;
    collection.insert(snippet1);
    collection.insert(snippet2);

    bool success = JsonFile<Snippet>::save(snippetFile.fileName(), &collection);

    QVERIFY(success);

    QTextStream in(&snippetFile);
    QString fileContent = in.readAll().trimmed();

    QVERIFY(fileContent.startsWith("{"));
    QVERIFY(fileContent.contains("\"snippets\": ["));
    QVERIFY(fileContent.contains("\"trigger\": \"abc\""));
    QVERIFY(fileContent.contains("\"trigger\": \"xyz\""));
    QVERIFY(fileContent.endsWith("}"));
}

void JsonSnippetFileTest::roundtripTest()
{
    QTemporaryFile snippetFile(this);
    if (!snippetFile.open())
        QFAIL("Failed to create temporary snippet file");

    Snippet snippet1;
    snippet1.trigger = "abc";
    snippet1.description = "description abc";
    snippet1.snippet = "content abc";
    snippet1.cursorPosition = 0;
    snippet1.builtIn = true;

    Snippet snippet2;
    snippet2.trigger = "xyz";
    snippet2.description = "description xyz";
    snippet2.snippet = "content xyz";
    snippet2.cursorPosition = 1;
    snippet2.builtIn = false;

    SnippetCollection collection1;
    collection1.insert(snippet1);
    collection1.insert(snippet2);

    bool saveSuccess = JsonFile<Snippet>::save(snippetFile.fileName(), &collection1);
    QVERIFY(saveSuccess);

    SnippetCollection collection2;
    bool loadSuccess = JsonFile<Snippet>::load(snippetFile.fileName(), &collection2);
    QVERIFY(loadSuccess);

    QCOMPARE(collection2.count(), 2);

    QCOMPARE(collection2.snippet("abc").description, snippet1.description);
    QCOMPARE(collection2.snippet("abc").snippet, snippet1.snippet);
    QCOMPARE(collection2.snippet("abc").cursorPosition, snippet1.cursorPosition);
    QCOMPARE(collection2.snippet("abc").builtIn, snippet1.builtIn);

    QCOMPARE(collection2.snippet("xyz").description, snippet2.description);
    QCOMPARE(collection2.snippet("xyz").snippet, snippet2.snippet);
    QCOMPARE(collection2.snippet("xyz").cursorPosition, snippet2.cursorPosition);
    QCOMPARE(collection2.snippet("xyz").builtIn, snippet2.builtIn);
}
