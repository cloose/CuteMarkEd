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
#include "styletest.h"

#include <QTest>

#include <styles/style.h>

void StyleTest::isEqualComparable()
{
    Style style1;
    style1.name = "abc";
    style1.markdownHighlighting = "markdownHighlighting 1";

    Style style2;
    style2.name = "abc";
    style2.markdownHighlighting = "markdownHighlighting 2";

    Style style3;
    style3.name = "xyz";
    style3.markdownHighlighting = "markdownHighlighting 1";

    QCOMPARE(style1 == style1, true);
    QCOMPARE(style1 == style2, true);
    QCOMPARE(style1 == style3, false);
}

void StyleTest::isInitializedAfterCreation()
{
    Style style;
    QVERIFY(style.name.isNull());
    QVERIFY(style.markdownHighlighting.isNull());
    QVERIFY(style.codeHighlighting.isNull());
    QVERIFY(style.previewStylesheet.isNull());
    QCOMPARE(style.builtIn, false);
}

