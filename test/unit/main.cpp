/*
 * Copyright 2013-2014 Christian Loose <christian.loose@hamburg.de>
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

#include "dictionarytest.h"
#include "jsonsnippettranslatortest.h"
#include "jsontranslatorfactorytest.h"
#include "slidelinemappingtest.h"
#include "snippetcollectiontest.h"
#include "completionlistmodeltest.h"
#include "snippettest.h"
#include "yamlheadercheckertest.h"

int main(int argc, char *argv[])
{
    int ret = 0;

    SnippetTest test;
    ret += QTest::qExec(&test, argc, argv);

    JsonSnippetTranslatorTest test2;
    ret += QTest::qExec(&test2, argc, argv);

    SnippetCollectionTest test3;
    ret += QTest::qExec(&test3, argc, argv);

    CompletionListModelTest test4;
    ret += QTest::qExec(&test4, argc, argv);

    DictionaryTest test5;
    ret += QTest::qExec(&test5, argc, argv);

    SlideLineMappingTest test6;
    ret += QTest::qExec(&test6, argc, argv);

    JsonTranslatorFactoryTest test7;
    ret += QTest::qExec(&test7, argc, argv);

    YamlHeaderCheckerTest test8;
    ret += QTest::qExec(&test8, argc, argv);

    return ret;
}
