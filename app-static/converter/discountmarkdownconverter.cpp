/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.  
 *     
 *     (3) The name of the author may not be used to
 *     endorse or promote products derived from this software without
 *     specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "discountmarkdownconverter.h"

extern "C" {
#ifdef Q_OS_WIN
#include <Windows.h>
#endif
#include <mkdio.h>
}

#include "markdowndocument.h"
#include "template/htmltemplate.h"

class DiscountMarkdownDocument : public MarkdownDocument
{
public:
    explicit DiscountMarkdownDocument(MMIOT *document) : discountDocument(document) {}
    ~DiscountMarkdownDocument() { mkd_cleanup(discountDocument); }

    MMIOT *document() const { return discountDocument; }

private:
    MMIOT *discountDocument;
};


DiscountMarkdownConverter::DiscountMarkdownConverter()
{
}

MarkdownDocument *DiscountMarkdownConverter::createDocument(const QString &text, ConverterOptions options)
{
    MMIOT *doc = 0;

    if (text.length() > 0) {
        QString markdownText(text);

        // text has to always end with a line break,
        // otherwise characters are missing in HTML
        if (!markdownText.endsWith('\n')) {
            markdownText.append('\n');
        }

        unsigned long converterOptions = translateConverterOptions(options);

        QByteArray utf8Data = markdownText.toUtf8();
        doc = mkd_string(utf8Data, utf8Data.length(), converterOptions);

        mkd_compile(doc, converterOptions);
    }

    return new DiscountMarkdownDocument(doc);
}

QString DiscountMarkdownConverter::renderAsHtml(MarkdownDocument *document)
{
    QString html;

    if (document) {
        DiscountMarkdownDocument *doc = dynamic_cast<DiscountMarkdownDocument*>(document);

        if (doc && doc->document()) {
            char *out;
            mkd_document(doc->document(), &out);

            html = QString::fromUtf8(out);
        }
    }

    return html;
}

QString DiscountMarkdownConverter::renderAsTableOfContents(MarkdownDocument *document)
{
    QString toc;

    if (document) {
        DiscountMarkdownDocument *doc = dynamic_cast<DiscountMarkdownDocument*>(document);

        if (doc && doc->document()) {
            // generate table of contents
            char *out;
            mkd_toc(doc->document(), &out);

            toc = QString::fromUtf8(out);
        }
    }

    return toc;
}

Template *DiscountMarkdownConverter::templateRenderer() const
{
    static HtmlTemplate htmlTemplate;
    return &htmlTemplate;
}

MarkdownConverter::ConverterOptions DiscountMarkdownConverter::supportedOptions() const
{
    return MarkdownConverter::AutolinkOption |
           MarkdownConverter::NoStrikethroughOption |
           MarkdownConverter::NoAlphaListOption |
           MarkdownConverter::NoDefinitionListOption |
           MarkdownConverter::NoSmartypantsOption |
           MarkdownConverter::ExtraFootnoteOption |
           MarkdownConverter::NoSuperscriptOption;
}

unsigned long DiscountMarkdownConverter::translateConverterOptions(ConverterOptions options) const
{
    unsigned long converterOptions = MKD_TOC | MKD_NOSTYLE;

    // autolink
    if (options.testFlag(MarkdownConverter::AutolinkOption)) {
        converterOptions |= MKD_AUTOLINK;
    }

    // strikethrough
    if (options.testFlag(MarkdownConverter::NoStrikethroughOption)) {
        converterOptions |= MKD_NOSTRIKETHROUGH;
    }

    // alphabetic lists
    if (options.testFlag(MarkdownConverter::NoAlphaListOption)) {
        converterOptions |= MKD_NOALPHALIST;
    }

    // definition lists
    if (options.testFlag(MarkdownConverter::NoDefinitionListOption)) {
        converterOptions |= MKD_NODLIST;
    }

    // SmartyPants
    if (options.testFlag(MarkdownConverter::NoSmartypantsOption)) {
        converterOptions |= MKD_NOPANTS;
    }

    // Footnotes
    if (options.testFlag(MarkdownConverter::ExtraFootnoteOption)) {
        converterOptions |= MKD_EXTRA_FOOTNOTE;
    }

    // Superscript
    if (options.testFlag(MarkdownConverter::NoSuperscriptOption)) {
        converterOptions |= MKD_NOSUPERSCRIPT;
    }

    return converterOptions;
}
