#ifndef DISCOUNTMARKDOWNCONVERTERTEST_H
#define DISCOUNTMARKDOWNCONVERTERTEST_H

#include <QObject>

class DiscountMarkdownConverter;


class DiscountMarkdownConverterTest : public QObject
{
    Q_OBJECT
    
private slots:
    void initTestCase();

    void convertsEmptyStringToEmptyHtml();
    void convertsMarkdownParagraphToHtml();

    void cleanupTestCase();

private:
    DiscountMarkdownConverter *converter;
};

#endif // DISCOUNTMARKDOWNCONVERTERTEST_H
