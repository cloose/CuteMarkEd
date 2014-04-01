#ifndef REVEALMARKDOWNCONVERTER_H
#define REVEALMARKDOWNCONVERTER_H

#include "markdownconverter.h"

class RevealMarkdownConverter : public MarkdownConverter
{
public:
    RevealMarkdownConverter();

    virtual MarkdownDocument *createDocument(const QString &text, ConverterOptions options);
    virtual QString renderAsHtml(MarkdownDocument *document);
    virtual QString renderAsTableOfContents(MarkdownDocument *document);

    virtual Template *templateRenderer() const;

    virtual ConverterOptions supportedOptions() const;
};

#endif // REVEALMARKDOWNCONVERTER_H
