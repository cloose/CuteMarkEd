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
#include "discountmarkdownconvertertest.h"

#include <QtTest>

#include <converter/discountmarkdownconverter.h>
#include "loremipsumtestdata.h"

void DiscountMarkdownConverterTest::initTestCase()
{
    converter = new DiscountMarkdownConverter();
}

void DiscountMarkdownConverterTest::convertsEmptyStringToEmptyHtml()
{
    QString html = transformMarkdownToHtml(QString());

    QVERIFY(html.isNull());
}

void DiscountMarkdownConverterTest::convertsMarkdownParagraphToHtml()
{
    QString markdown = "This is an example";

    QString html = transformMarkdownToHtml(markdown);

    QVERIFY(!html.isEmpty());
    QCOMPARE(html, QStringLiteral("<p>This is an example</p>"));
}

void DiscountMarkdownConverterTest::convertsMarkdownHeaderToHtml()
{
    QString html = transformMarkdownToHtml(QStringLiteral("# This is an example"));

    if (isIdAnchorDisabled(html))
        QCOMPARE(html, QStringLiteral("<a name=\"This.is.an.example\"></a>\n<h1>This is an example</h1>"));
    else
        QCOMPARE(html, QStringLiteral("<h1 id=\"This.is.an.example\">This is an example</h1>"));

    html = transformMarkdownToHtml(QStringLiteral("## This is an example"));

    if (isIdAnchorDisabled(html))
        QCOMPARE(html, QStringLiteral("<a name=\"This.is.an.example\"></a>\n<h2>This is an example</h2>"));
    else
        QCOMPARE(html, QStringLiteral("<h2 id=\"This.is.an.example\">This is an example</h2>"));
}

void DiscountMarkdownConverterTest::preservesGermanUmlautsInHtml()
{
#if defined(Q_CC_MSVC)
    QSKIP("This causes an assert with MSVC");
#endif

    QString markdown = QStringLiteral("äöü");

    QString html = transformMarkdownToHtml(markdown);

    QVERIFY(!html.isEmpty());
    QCOMPARE(html, QStringLiteral("<p>äöü</p>"));
}

void DiscountMarkdownConverterTest::supportsSuperscriptIfEnabled()
{
    QString html = transformMarkdownToHtml(QStringLiteral("a^2"));
    QCOMPARE(html, QStringLiteral("<p>a<sup>2</sup></p>"));
}

void DiscountMarkdownConverterTest::ignoresSuperscriptIfDisabled()
{
    MarkdownDocument *doc = converter->createDocument(QStringLiteral("a^2"), DiscountMarkdownConverter::NoSuperscriptOption);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("<p>a^2</p>"));
}

void DiscountMarkdownConverterTest::benchmark_data()
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

void DiscountMarkdownConverterTest::benchmark()
{
    QFETCH(QString, text);
    QBENCHMARK {
        MarkdownDocument *doc = converter->createDocument(text, 0);
        QString html = converter->renderAsHtml(doc);
    }
}

void DiscountMarkdownConverterTest::benchmarkTableOfContents_data()
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

void DiscountMarkdownConverterTest::benchmarkTableOfContents()
{
    QFETCH(QString, text);
    QBENCHMARK {
        MarkdownDocument *doc = converter->createDocument(text, 0);
        QString toc = converter->renderAsTableOfContents(doc);
    }
}

void DiscountMarkdownConverterTest::cleanupTestCase()
{
    delete converter;
}

bool DiscountMarkdownConverterTest::isIdAnchorDisabled(const QString &html)
{
    // On some linux systems (e.g. Fedora 21) the compile option --with-id-anchor is
    // disabled for the discount library
    return html.startsWith("<a name=");
}
    
QString DiscountMarkdownConverterTest::transformMarkdownToHtml(const QString &text)
{
    MarkdownDocument *doc = converter->createDocument(text, 0);
    return converter->renderAsHtml(doc);
}
