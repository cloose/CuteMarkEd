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

void DiscountMarkdownConverterTest::supportsSuperscriptIfEnabled()
{
    MarkdownDocument *doc = converter->createDocument(QStringLiteral("a^2"), 0);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("<p>a<sup>2</sup></p>"));
}

void DiscountMarkdownConverterTest::ignoresSuperscriptIfDisabled()
{
    MarkdownDocument *doc = converter->createDocument(QStringLiteral("a^2"), DiscountMarkdownConverter::NoSuperscriptOption);
    QCOMPARE(converter->renderAsHtml(doc), QStringLiteral("<p>a^2</p>"));
}

void DiscountMarkdownConverterTest::benchmark_data()
{
    QTest::addColumn<QString>("text");
    QTest::newRow("short text") << QStringLiteral("ArbitraryText");
    QString fiveLinesText = QStringLiteral("# Lorem ipsum dolor sit amet\n"
                                           "consectetur adipiscing elit. Quisque dui tortor, feugiat in sapien blandit, consequat rutrum neque. Donec nec interdum mauris. Vivamus quis egestas eros. Suspendisse et nisl blandit, ultrices massa tincidunt, hendrerit orci. Cras iaculis lacus magna, quis lacinia massa venenatis venenatis. Sed sed elit neque. Proin ornare magna ante, eu aliquam lorem lobortis ut. Aliquam auctor eget lacus ut eleifend. Sed blandit dapibus mi, vel commodo magna pharetra id. Maecenas egestas ultrices urna, a vestibulum ipsum fringilla a. Vivamus luctus enim nisi, ut posuere odio cursus non. Suspendisse maximus ullamcorper tortor ut mollis. Nam nec nibh pellentesque, tristique elit eu, pulvinar nibh.\n"
                                           "\n"
                                           "Maecenas in nisi eu neque fermentum gravida vitae vitae libero. Quisque efficitur mauris a elit luctus, ac consequat orci varius. Etiam faucibus dolor quis lorem sagittis dapibus. Proin vitae arcu id dolor hendrerit placerat vitae ac dolor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed faucibus, dui sed viverra maximus, justo lacus elementum orci, ut fermentum risus diam nec ipsum. Proin non felis vitae turpis hendrerit posuere. Vestibulum bibendum, ante eget efficitur accumsan, mauris est aliquet tellus, eget laoreet magna leo sit amet nulla. Nunc eget sollicitudin dolor, vitae dignissim nulla. Suspendisse condimentum orci sit amet semper ullamcorper. Maecenas nec felis risus. Praesent congue rhoncus velit, quis accumsan magna tempor eu. Mauris eu pharetra elit. Aliquam pretium augue lobortis nisl ultricies, dapibus efficitur risus viverra. Nam elementum lacinia dolor, at hendrerit nibh auctor in. Fusce sodales molestie nunc, at feugiat lacus hendrerit ac.\n"
                                           "\n"
                                           "Donec malesuada risus mi, a porttitor enim feugiat et. In sit amet nisi leo. Maecenas finibus tortor vitae neque tristique vestibulum. Nulla maximus magna arcu, sit amet maximus est pellentesque elementum. Nulla sit amet odio vitae nunc finibus consectetur quis in justo. Sed ac est ligula. Aenean sed mauris vel lacus placerat interdum.\n"
                                           "\n"
                                           "Quisque efficitur sem et magna gravida, ut dapibus ante elementum. Pellentesque in odio tortor. Morbi tincidunt lacus arcu, et maximus purus placerat vel. Fusce placerat pretium ex, iaculis ullamcorper erat mollis vitae. Mauris tristique dolor ut est dapibus, eget ultrices purus sodales. Nullam tristique rhoncus pretium. Sed aliquam dolor imperdiet quam suscipit, in iaculis tellus porttitor. Aliquam erat volutpat. Nunc fermentum, justo et hendrerit aliquet, nisi libero congue ipsum, vitae mollis augue risus id orci. Maecenas interdum est eu eros dapibus, in imperdiet justo pretium. Sed sit amet nisl malesuada, vehicula leo eget, fermentum enim. Integer volutpat in erat et ultricies.\n"
                                           "\n"
                                           "Morbi vulputate, risus id ultrices porttitor, diam metus suscipit sem, nec sagittis nisi nulla sed nunc. Aenean vitae aliquam erat. Sed non erat hendrerit, congue est non, semper ex. Mauris lobortis molestie neque quis tristique. Nulla pulvinar dui euismod, venenatis quam in, interdum magna. Sed nisi erat, vehicula vitae pulvinar non, facilisis ac felis. In ex nunc, faucibus id leo eget, tincidunt maximus metus. Morbi placerat vulputate leo, a iaculis est volutpat quis. Donec mi leo, finibus ut ligula in, vulputate ornare neque. Duis eget urna sed enim mattis laoreet. Donec at nibh mollis, rhoncus eros vel, ullamcorper ante. Donec ultrices orci vel nisi sagittis consequat. Maecenas sed elit non mi commodo eleifend. Morbi sapien dui, ultrices nec molestie id, elementum et purus.\n");
    QTest::newRow("5 lines text") << fiveLinesText;
    QTest::newRow("long text") << (fiveLinesText + fiveLinesText + fiveLinesText + fiveLinesText + fiveLinesText);
}

void DiscountMarkdownConverterTest::benchmark()
{
    QFETCH(QString, text);
    QBENCHMARK {
        MarkdownDocument *doc = converter->createDocument(text, 0);
        QString html = converter->renderAsHtml(doc);
    }
}

void DiscountMarkdownConverterTest::cleanupTestCase()
{
    delete converter;
}
