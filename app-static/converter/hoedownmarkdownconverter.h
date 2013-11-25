#ifndef HOEDOWNMARKDOWNCONVERTER_H
#define HOEDOWNMARKDOWNCONVERTER_H

#include "markdownconverter.h"

class HoedownMarkdownConverter : public MarkdownConverter
{
public:
    HoedownMarkdownConverter();

    virtual MarkdownDocument *createDocument(const QString &text);
    virtual QString renderAsHtml(MarkdownDocument *document);
    virtual QString renderAsTableOfContents(MarkdownDocument *document);
};

#endif // HOEDOWNMARKDOWNCONVERTER_H
