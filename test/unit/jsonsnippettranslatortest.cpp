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
#include "jsonsnippettranslatortest.h"

#include <QtTest>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <snippets/jsonsnippettranslator.h>
#include <snippets/snippet.h>
#include <snippets/snippetcollection.h>


QJsonDocument NewSnippetDocumentWithObject(const QJsonObject &jsonObject)
{
    QJsonArray snippetArray;
    snippetArray.append(jsonObject);

    QJsonObject object;
    object.insert("snippets", snippetArray);

    QJsonDocument doc(object);
    return doc;
}

void JsonSnippetTranslatorTest::initTestCase()
{
    translator = new JsonSnippetTranslator();
}

void JsonSnippetTranslatorTest::translatesJsonDocumentToSnippets()
{
    Snippet expected;
    expected.trigger = "trigger";
    expected.description = "description";
    expected.snippet = "snippet";
    expected.cursorPosition = 1;
    expected.builtIn = true;

    QJsonObject jsonObject;
    jsonObject.insert("trigger", expected.trigger);
    jsonObject.insert("description", expected.description);
    jsonObject.insert("snippet", expected.snippet);
    jsonObject.insert("cursor", expected.cursorPosition);
    jsonObject.insert("builtIn", expected.builtIn);

    QJsonDocument doc = NewSnippetDocumentWithObject(jsonObject);

    SnippetCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 1);
    QCOMPARE(collection.at(0).trigger, expected.trigger);
    QCOMPARE(collection.at(0).description, expected.description);
    QCOMPARE(collection.at(0).snippet, expected.snippet);
    QCOMPARE(collection.at(0).cursorPosition, expected.cursorPosition);
    QCOMPARE(collection.at(0).builtIn, expected.builtIn);
}

void JsonSnippetTranslatorTest::translatesEmptyJsonDocumentToEmptySnippets()
{
    Snippet expected;
    expected.trigger = QString();
    expected.description = QString();
    expected.snippet = QString();
    expected.cursorPosition = 0;
    expected.builtIn = false;

    QJsonObject emptyJsonObject;
    QJsonDocument doc = NewSnippetDocumentWithObject(emptyJsonObject);

    SnippetCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 1);
    QCOMPARE(collection.at(0).trigger, expected.trigger);
    QCOMPARE(collection.at(0).description, expected.description);
    QCOMPARE(collection.at(0).snippet, expected.snippet);
    QCOMPARE(collection.at(0).cursorPosition, expected.cursorPosition);
    QCOMPARE(collection.at(0).builtIn, expected.builtIn);
}

void JsonSnippetTranslatorTest::defectIfJsonDocumentIsInvalid()
{
    QJsonDocument doc;

    SnippetCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(!success);
    QCOMPARE(collection.count(), 0);
}

void JsonSnippetTranslatorTest::translatesSnippetCollectionToJsonDocument()
{
    Snippet snippet;
    snippet.trigger = "trigger";
    snippet.description = "description";
    snippet.snippet = "snippet";
    snippet.cursorPosition = 1;
    snippet.builtIn = true;

    SnippetCollection collection;
    collection.insert(snippet);

    QJsonObject expected;
    expected.insert("trigger", snippet.trigger);
    expected.insert("description", snippet.description);
    expected.insert("snippet", snippet.snippet);
    expected.insert("cursor", snippet.cursorPosition);
    expected.insert("builtIn", snippet.builtIn);

    QJsonDocument actual = translator->createDocument(&collection);

    QVERIFY(actual.isObject());
    QVERIFY(actual.object().contains("snippets"));
    QVERIFY(actual.object().value("snippets").isArray());

    QJsonObject actualObject = actual.object().value("snippets").toArray().first().toObject();
    QCOMPARE(actualObject["trigger"], expected["trigger"]);
    QCOMPARE(actualObject["description"], expected["description"]);
    QCOMPARE(actualObject["snippet"], expected["snippet"]);
    QCOMPARE(actualObject["cursorPosition"], expected["cursorPosition"]);
    QCOMPARE(actualObject["builtIn"], expected["builtIn"]);
}

void JsonSnippetTranslatorTest::cleanupTestCase()
{
    delete translator;
}

