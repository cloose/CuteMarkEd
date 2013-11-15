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

#include <QTest>

#include <snippets/jsonsnippettranslator.h>
#include <snippets/snippet.h>

void JsonSnippetTranslatorTest::initTestCase()
{
    translator = new JsonSnippetTranslator();
}

void JsonSnippetTranslatorTest::translatesJsonObjectToSnippet()
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

    Snippet actual = translator->fromJsonObject(jsonObject);

    QCOMPARE(actual.trigger, expected.trigger);
    QCOMPARE(actual.description, expected.description);
    QCOMPARE(actual.snippet, expected.snippet);
    QCOMPARE(actual.cursorPosition, expected.cursorPosition);
    QCOMPARE(actual.builtIn, expected.builtIn);
}

void JsonSnippetTranslatorTest::translatesEmptyJsonObjectToEmptySnippet()
{
    Snippet expected;
    expected.trigger = QString();
    expected.description = QString();
    expected.snippet = QString();
    expected.cursorPosition = 0;
    expected.builtIn = false;

    QJsonObject emptyJsonObject;

    Snippet actual = translator->fromJsonObject(emptyJsonObject);

    QCOMPARE(actual.trigger, expected.trigger);
    QCOMPARE(actual.description, expected.description);
    QCOMPARE(actual.snippet, expected.snippet);
    QCOMPARE(actual.cursorPosition, expected.cursorPosition);
    QCOMPARE(actual.builtIn, expected.builtIn);
}

void JsonSnippetTranslatorTest::translatesSnippetToJsonObject()
{
    Snippet snippet;
    snippet.trigger = "trigger";
    snippet.description = "description";
    snippet.snippet = "snippet";
    snippet.cursorPosition = 1;
    snippet.builtIn = true;

    QJsonObject expected;
    expected.insert("trigger", snippet.trigger);
    expected.insert("description", snippet.description);
    expected.insert("snippet", snippet.snippet);
    expected.insert("cursor", snippet.cursorPosition);
    expected.insert("builtIn", snippet.builtIn);

    QJsonObject actual = translator->toJsonObject(snippet);

    QCOMPARE(actual["trigger"], expected["trigger"]);
    QCOMPARE(actual["description"], expected["description"]);
    QCOMPARE(actual["snippet"], expected["snippet"]);
    QCOMPARE(actual["cursorPosition"], expected["cursorPosition"]);
    QCOMPARE(actual["builtIn"], expected["builtIn"]);
}

void JsonSnippetTranslatorTest::cleanupTestCase()
{
    delete translator;
}


