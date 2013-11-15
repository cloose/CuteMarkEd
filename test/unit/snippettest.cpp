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
#include "snippettest.h"

#include <QTest>

#include <snippets/snippet.h>

void SnippetTest::isLessThanComparable()
{
    Snippet snippet1;
    snippet1.trigger = "abc";

    Snippet snippet2;
    snippet2.trigger = "xyz";

    QCOMPARE(snippet1 < snippet2, true);
    QCOMPARE(snippet2 < snippet1, false);
    QCOMPARE(snippet1 < snippet1, false);
}

void SnippetTest::isInitializedAfterCreation()
{
    Snippet snippet;
    QVERIFY(snippet.trigger.isNull());
    QVERIFY(snippet.description.isNull());
    QVERIFY(snippet.snippet.isNull());
    QCOMPARE(snippet.cursorPosition, 0);
    QCOMPARE(snippet.builtIn, false);
}

void SnippetTest::translatesJsonObjectToSnippet()
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

    Snippet actual = Snippet::fromJsonObject(jsonObject);

    QCOMPARE(actual.trigger, expected.trigger);
    QCOMPARE(actual.description, expected.description);
    QCOMPARE(actual.snippet, expected.snippet);
    QCOMPARE(actual.cursorPosition, expected.cursorPosition);
    QCOMPARE(actual.builtIn, expected.builtIn);
}

void SnippetTest::translatesEmptyJsonObjectToEmptySnippet()
{
    Snippet expected;
    expected.trigger = QString();
    expected.description = QString();
    expected.snippet = QString();
    expected.cursorPosition = 0;
    expected.builtIn = false;

    QJsonObject emptyJsonObject;

    Snippet actual = Snippet::fromJsonObject(emptyJsonObject);

    QCOMPARE(actual.trigger, expected.trigger);
    QCOMPARE(actual.description, expected.description);
    QCOMPARE(actual.snippet, expected.snippet);
    QCOMPARE(actual.cursorPosition, expected.cursorPosition);
    QCOMPARE(actual.builtIn, expected.builtIn);
}

void SnippetTest::translatesSnippetToJsonObject()
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

    QJsonObject actual = Snippet::toJsonObject(snippet);

    QCOMPARE(actual["trigger"], expected["trigger"]);
    QCOMPARE(actual["description"], expected["description"]);
    QCOMPARE(actual["snippet"], expected["snippet"]);
    QCOMPARE(actual["cursorPosition"], expected["cursorPosition"]);
    QCOMPARE(actual["builtIn"], expected["builtIn"]);
}
