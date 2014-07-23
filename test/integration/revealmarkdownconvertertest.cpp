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
#include "revealmarkdownconvertertest.h"

#include <QtTest>

#include <converter/revealmarkdownconverter.h>

void RevealMarkdownConverterTest::initTestCase()
{
    converter = new RevealMarkdownConverter();
}

void RevealMarkdownConverterTest::convertsEmptyStringToEmptyHtml()
{
    MarkdownDocument *doc = converter->createDocument(QString(), 0);
    QString html = converter->renderAsHtml(doc);

    QVERIFY(html.isNull());
}

void RevealMarkdownConverterTest::returnsAnyMarkdownTextUnchanged()
{
    MarkdownDocument *doc = converter->createDocument(QStringLiteral("This is an example"), 0);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("This is an example"));

    doc = converter->createDocument(QStringLiteral("# This is an example"), 0);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("# This is an example"));

    doc = converter->createDocument(QStringLiteral("## This is an example"), 0);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("## This is an example"));
}

void RevealMarkdownConverterTest::preservesGermanUmlautsInHtml()
{
    QString markdown = QStringLiteral("äöüß");

    MarkdownDocument *doc = converter->createDocument(markdown, 0);
    QString html = converter->renderAsHtml(doc);

    QVERIFY(!html.isEmpty());
    QCOMPARE(html, QStringLiteral("äöüß"));
}

void RevealMarkdownConverterTest::cleanupTestCase()
{
    delete converter;
}
