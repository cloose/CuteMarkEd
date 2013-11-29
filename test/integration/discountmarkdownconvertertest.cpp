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

void DiscountMarkdownConverterTest::cleanupTestCase()
{
    delete converter;
}
