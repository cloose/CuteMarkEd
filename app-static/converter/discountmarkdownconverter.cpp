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

        if (doc->document()) {
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

        if (doc->document()) {
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
