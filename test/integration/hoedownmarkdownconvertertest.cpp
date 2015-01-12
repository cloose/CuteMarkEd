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
#include "hoedownmarkdownconvertertest.h"

#include <QtTest>

#include <converter/hoedownmarkdownconverter.h>
#include "loremipsumtestdata.h"

void HoedownMarkdownConverterTest::initTestCase()
{
    converter = new HoedownMarkdownConverter();
}

void HoedownMarkdownConverterTest::convertsEmptyStringToEmptyHtml()
{
    MarkdownDocument *doc = converter->createDocument(QString(), 0);
    QString html = converter->renderAsHtml(doc);

    QVERIFY(html.isNull());
}

void HoedownMarkdownConverterTest::convertsMarkdownParagraphToHtml()
{
    QString markdown = "This is an example";

    MarkdownDocument *doc = converter->createDocument(markdown, 0);
    QString html = converter->renderAsHtml(doc);

    QVERIFY(!html.isEmpty());
    QVERIFY2(html.contains("<p>This is an example</p>"), qPrintable(html));
}

void HoedownMarkdownConverterTest::preservesGermanUmlautsInHtml()
{
    QString markdown = QStringLiteral("äöüß");

    MarkdownDocument *doc = converter->createDocument(markdown, 0);
    QString html = converter->renderAsHtml(doc);

    QVERIFY(!html.isEmpty());
    QVERIFY2(html.contains(QStringLiteral("<p>äöüß</p>")), qPrintable(html));
}

void HoedownMarkdownConverterTest::supportsSuperscriptIfEnabled()
{
    MarkdownDocument *doc = converter->createDocument(QStringLiteral("a^2"), 0);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("<p>a<sup>2</sup></p>\n"));
}

void HoedownMarkdownConverterTest::ignoresSuperscriptIfDisabled()
{
    MarkdownDocument *doc = converter->createDocument(QStringLiteral("a^2"), HoedownMarkdownConverter::NoSuperscriptOption);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("<p>a^2</p>\n"));
}

void HoedownMarkdownConverterTest::benchmark_data()
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

void HoedownMarkdownConverterTest::benchmark()
{
    QFETCH(QString, text);
    QBENCHMARK {
        MarkdownDocument *doc = converter->createDocument(text, 0);
        QString html = converter->renderAsHtml(doc);
    }
}

void HoedownMarkdownConverterTest::benchmarkTableOfContents_data()
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

void HoedownMarkdownConverterTest::benchmarkTableOfContents()
{
    QFETCH(QString, text);
    QBENCHMARK {
        MarkdownDocument *doc = converter->createDocument(text, 0);
        QString toc = converter->renderAsTableOfContents(doc);
    }
}

void HoedownMarkdownConverterTest::cleanupTestCase()
{
    delete converter;
}
