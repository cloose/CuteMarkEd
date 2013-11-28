#ifndef HOEDOWNMARKDOWNCONVERTERTEST_H
#define HOEDOWNMARKDOWNCONVERTERTEST_H

#include <QObject>

class HoedownMarkdownConverter;


class HoedownMarkdownConverterTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void convertsEmptyStringToEmptyHtml();
    void convertsMarkdownParagraphToHtml();

    void cleanupTestCase();

private:
    HoedownMarkdownConverter *converter;
};

#endif // HOEDOWNMARKDOWNCONVERTERTEST_H
