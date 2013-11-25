#ifndef MARKDOWNCONVERTER_H
#define MARKDOWNCONVERTER_H

#include <QString>

class MarkdownDocument;


class MarkdownConverter
{
public:
    virtual ~MarkdownConverter() {}

    virtual MarkdownDocument *createDocument(const QString &text) = 0;
    virtual QString renderAsHtml(MarkdownDocument *document) = 0;
    virtual QString renderAsTableOfContents(MarkdownDocument *document) = 0;
};

#endif // MARKDOWNCONVERTER_H
