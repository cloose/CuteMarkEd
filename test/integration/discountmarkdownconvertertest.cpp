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
#include "discountmarkdownconvertertest.h"

#include <QtTest>

#include <converter/discountmarkdownconverter.h>

void DiscountMarkdownConverterTest::initTestCase()
{
    converter = new DiscountMarkdownConverter();
}

void DiscountMarkdownConverterTest::convertsEmptyStringToEmptyHtml()
{
    MarkdownDocument *doc = converter->createDocument(QString(), 0);
    QString html = converter->renderAsHtml(doc);

    QVERIFY(html.isNull());
}

void DiscountMarkdownConverterTest::convertsMarkdownParagraphToHtml()
{
    QString markdown = "This is an example";

    MarkdownDocument *doc = converter->createDocument(markdown, 0);
    QString html = converter->renderAsHtml(doc);

    QVERIFY(!html.isEmpty());
    QCOMPARE(html, QStringLiteral("<p>This is an example</p>"));
}

void DiscountMarkdownConverterTest::convertsMarkdownHeaderToHtml()
{
    MarkdownDocument *doc = converter->createDocument(QStringLiteral("# This is an example"), 0);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("<h1 id=\"This.is.an.example\">This is an example</h1>"));

    doc = converter->createDocument(QStringLiteral("## This is an example"), 0);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("<h2 id=\"This.is.an.example\">This is an example</h2>"));
}

void DiscountMarkdownConverterTest::preservesGermanUmlautsInHtml()
{
    QString markdown = QStringLiteral("äöü");

    MarkdownDocument *doc = converter->createDocument(markdown, 0);
    QString html = converter->renderAsHtml(doc);

    QVERIFY(!html.isEmpty());
    QCOMPARE(html, QStringLiteral("<p>äöü</p>"));
}

void DiscountMarkdownConverterTest::cleanupTestCase()
{
    delete converter;
}
