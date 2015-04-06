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
#include "pmhmarkdownparsertest.h"

#include <QtTest>

#include <pmhmarkdownparser.h>
#include "loremipsumtestdata.h"

void PmhMarkdownParserTest::initTestCase()
{
    parser = new PmhMarkdownParser();
}

void PmhMarkdownParserTest::cleanupTestCase()
{
    delete parser;
}

void PmhMarkdownParserTest::returnsEmptyMapForEmptyMarkdownDocument()
{
    QMap<MarkdownElement::Type, QList<MarkdownElement> > elements = parser->parseMarkdown("");
    QVERIFY(elements.isEmpty());
}

void PmhMarkdownParserTest::returnsNoEntryForNonExistingMarkdownElements()
{
    QMap<MarkdownElement::Type, QList<MarkdownElement> > elements = parser->parseMarkdown("# Header 1\n");

    QVERIFY(!elements.isEmpty());
    QVERIFY(elements[MarkdownElement::LINK].isEmpty());
}

void PmhMarkdownParserTest::returnsEntryForMarkdownElement()
{
    QMap<MarkdownElement::Type, QList<MarkdownElement> > elements = parser->parseMarkdown("# Header 1\n");

    QVERIFY(!elements.isEmpty());
    QVERIFY(!elements[MarkdownElement::H1].isEmpty());
}

void PmhMarkdownParserTest::returnsListOfEntriesForSingleMarkdownElementType()
{
    QMap<MarkdownElement::Type, QList<MarkdownElement> > elements = parser->parseMarkdown("# Header 1a\n"
                                                                                          "# Header 1b\n");

    QVERIFY(!elements.isEmpty());
    QCOMPARE(elements[MarkdownElement::H1].count(), 2);
}

void PmhMarkdownParserTest::entryKnowsItsMarkdownElementType() 
{
    QMap<MarkdownElement::Type, QList<MarkdownElement> > elements = parser->parseMarkdown("# Header 1\n");

    MarkdownElement element = elements[MarkdownElement::H1].first();

    QCOMPARE(element.type, MarkdownElement::H1);
}

void PmhMarkdownParserTest::entryHasStartAndEndPosition()
{
    QMap<MarkdownElement::Type, QList<MarkdownElement> > elements = parser->parseMarkdown("# Header 1\n");

    MarkdownElement element = elements[MarkdownElement::H1].first();

    QCOMPARE(element.start, (unsigned long)0);
    // parser adds two additional \n and returns position before last \n 
    // so we get 9 char + 2 \n = 11
    QCOMPARE(element.end, (unsigned long)11); 
}

void PmhMarkdownParserTest::benchmark_data()
{
    QTest::addColumn<QString>("text");
    QTest::newRow("500 words text") << fiveHundredWordsLoremIpsumText;
    QString twoThousandWordsLoremIpsumText = (fiveHundredWordsLoremIpsumText +
                                              fiveHundredWordsLoremIpsumText +
                                              fiveHundredWordsLoremIpsumText +
                                              fiveHundredWordsLoremIpsumText);
    QTest::newRow("2000 words text") << twoThousandWordsLoremIpsumText;
    QString tenThousandWordsLoremIpsumText = (twoThousandWordsLoremIpsumText +
                                              twoThousandWordsLoremIpsumText +
                                              twoThousandWordsLoremIpsumText +
                                              twoThousandWordsLoremIpsumText +
                                              twoThousandWordsLoremIpsumText);
    QTest::newRow("10000 words text") << tenThousandWordsLoremIpsumText;
}

void PmhMarkdownParserTest::benchmark()
{
    QFETCH(QString, text);
    QBENCHMARK {
        QMap<MarkdownElement::Type, QList<MarkdownElement> > elements = parser->parseMarkdown(text);
    }
}
