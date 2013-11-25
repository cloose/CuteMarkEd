#ifndef DISCOUNTMARKDOWNCONVERTER_H
#define DISCOUNTMARKDOWNCONVERTER_H

#include "markdownconverter.h"

class DiscountMarkdownConverter : public MarkdownConverter
{
public:
    DiscountMarkdownConverter();

    virtual MarkdownDocument *createDocument(const QString &text);
    virtual QString renderAsHtml(MarkdownDocument *document);
    virtual QString renderAsTableOfContents(MarkdownDocument *document);
};

#endif // DISCOUNTMARKDOWNCONVERTER_H
