#include "hoedownmarkdownconvertertest.h"

#include <QtTest>

#include <converter/hoedownmarkdownconverter.h>

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
    QVERIFY(html.contains("<p>This is an example</p>"));
}

void HoedownMarkdownConverterTest::cleanupTestCase()
{
    delete converter;
}
