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
#include "themetest.h"

#include <QTest>

#include <themes/theme.h>

static const QLatin1String A_THEME_NAME("name");
static const QLatin1String A_MARKDOWN_HIGHLIGHTING("markdown");
static const QLatin1String A_CODE_HIGHLIGHTING("code");
static const QLatin1String A_PREVIEW_STYLESHEET("preview");

void ThemeTest::isLessThanComparable()
{
    Theme theme1("abc", A_MARKDOWN_HIGHLIGHTING, A_CODE_HIGHLIGHTING, A_PREVIEW_STYLESHEET);

    Theme theme2("xyz", A_MARKDOWN_HIGHLIGHTING, A_CODE_HIGHLIGHTING, A_PREVIEW_STYLESHEET);

    QCOMPARE(theme1 < theme2, true);
    QCOMPARE(theme2 < theme1, false);
    QCOMPARE(theme1 < theme1, false);
}

void ThemeTest::isEqualComparable()
{
    Theme theme1("abc", A_MARKDOWN_HIGHLIGHTING, A_CODE_HIGHLIGHTING, A_PREVIEW_STYLESHEET);

    Theme theme2("abc", A_MARKDOWN_HIGHLIGHTING, A_CODE_HIGHLIGHTING, A_PREVIEW_STYLESHEET);

    Theme theme3("xyz", A_MARKDOWN_HIGHLIGHTING, A_CODE_HIGHLIGHTING, A_PREVIEW_STYLESHEET);

    QCOMPARE(theme1 == theme1, true);
    QCOMPARE(theme1 == theme2, true);
    QCOMPARE(theme1 == theme3, false);
}

void ThemeTest::throwsIfNameIsEmpty()
{
    try {
        Theme theme("", A_MARKDOWN_HIGHLIGHTING, A_CODE_HIGHLIGHTING, A_PREVIEW_STYLESHEET);
        QFAIL("Expected exception of type runtime_error not thrown");
    } catch(const std::runtime_error &) {} 
}

void ThemeTest::throwsIfMarkdownHighlightingIsEmpty()
{
    try {
        Theme theme(A_THEME_NAME, "", A_CODE_HIGHLIGHTING, A_PREVIEW_STYLESHEET);
        QFAIL("Expected exception of type runtime_error not thrown");
    } catch(const std::runtime_error &) {} 
}

void ThemeTest::throwsIfCodeHighlightingIsEmpty()
{
    try {
        Theme theme(A_THEME_NAME, A_MARKDOWN_HIGHLIGHTING, "", A_PREVIEW_STYLESHEET);
        QFAIL("Expected exception of type runtime_error not thrown");
    } catch(const std::runtime_error &) {} 
}

void ThemeTest::throwsIfPreviewStylesheetIsEmpty()
{
    try {
        Theme theme(A_THEME_NAME, A_MARKDOWN_HIGHLIGHTING, A_CODE_HIGHLIGHTING, "");
        QFAIL("Expected exception of type runtime_error not thrown");
    } catch(const std::runtime_error &) {} 
}


