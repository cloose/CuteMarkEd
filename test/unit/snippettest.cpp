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
