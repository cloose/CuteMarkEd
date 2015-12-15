/*
 * Copyright 2013-2015 Christian Loose <christian.loose@hamburg.de>
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
#include <QTest>

#include <QApplication>

#include "discountmarkdownconvertertest.h"
#include "htmlpreviewcontrollertest.h"
#include "htmltemplatetest.h"
#include "jsonsnippetfiletest.h"
#include "jsonthemefiletest.h"
#include "pmhmarkdownparsertest.h"
#include "revealmarkdownconvertertest.h"
#include "themecollectiontest.h"

#ifdef ENABLE_HOEDOWN
#include "hoedownmarkdownconvertertest.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int ret = 0;

    DiscountMarkdownConverterTest test;
    ret += QTest::qExec(&test, argc, argv);

#ifdef ENABLE_HOEDOWN
    HoedownMarkdownConverterTest test2;
    ret += QTest::qExec(&test2, argc, argv);
#endif

    RevealMarkdownConverterTest test3;
    ret += QTest::qExec(&test3, argc, argv);

    JsonSnippetFileTest test4;
    ret += QTest::qExec(&test4, argc, argv);

    PmhMarkdownParserTest test5;
    ret += QTest::qExec(&test5, argc, argv);

    HtmlPreviewControllerTest test6;
    ret += QTest::qExec(&test6, argc, argv);

    HtmlTemplateTest test7;
    ret += QTest::qExec(&test7, argc, argv);

    JsonThemeFileTest test8;
    ret += QTest::qExec(&test8, argc, argv);

    ThemeCollectionTest test9;
    ret += QTest::qExec(&test9, argc, argv);

    return ret;
}

