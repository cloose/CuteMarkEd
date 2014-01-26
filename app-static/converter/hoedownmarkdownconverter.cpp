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
#include "hoedownmarkdownconverter.h"

extern "C" {
#include <src/html.h>
#include <src/markdown.h>
}

#include "markdowndocument.h"

class HoedownMarkdownDocument : public MarkdownDocument
{
public:
    explicit HoedownMarkdownDocument(hoedown_buffer *document, unsigned long options) :
        hoedownDocument(document),
        converterOptions(options)
    {}
    ~HoedownMarkdownDocument() { hoedown_buffer_free(hoedownDocument); }

    hoedown_buffer *document() const { return hoedownDocument; }
    unsigned long options() const { return converterOptions; }

private:
    hoedown_buffer *hoedownDocument;
    unsigned long converterOptions;
};


HoedownMarkdownConverter::HoedownMarkdownConverter()
{
}

MarkdownDocument *HoedownMarkdownConverter::createDocument(const QString &text, ConverterOptions options)
{
    hoedown_buffer *doc = 0;

    if (text.length() > 0) {
        QString markdownText(text);

        QByteArray utf8Data = markdownText.toUtf8();
        doc = hoedown_buffer_new(utf8Data.length());
        hoedown_buffer_puts(doc, utf8Data.data());
    }

    return new HoedownMarkdownDocument(doc, translateConverterOptions(options));
}

QString HoedownMarkdownConverter::renderAsHtml(MarkdownDocument *document)
{
    QString html;

    if (document) {
        HoedownMarkdownDocument *doc = dynamic_cast<HoedownMarkdownDocument*>(document);

        if (doc->document()) {
            hoedown_buffer *in = doc->document();
            hoedown_buffer *out = hoedown_buffer_new(64);

            hoedown_renderer *renderer = hoedown_html_renderer_new(0, 16);
            hoedown_markdown *markdown = hoedown_markdown_new(doc->options(), 16, renderer);

            hoedown_markdown_render(out, in->data, in->size, markdown);

            hoedown_markdown_free(markdown);
            hoedown_html_renderer_free(renderer);

            html = QString::fromUtf8(hoedown_buffer_cstr(out));

            hoedown_buffer_free(out);
        }
    }

    return html;
}

QString HoedownMarkdownConverter::renderAsTableOfContents(MarkdownDocument *document)
{
    QString toc;

    if (document) {
        HoedownMarkdownDocument *doc = dynamic_cast<HoedownMarkdownDocument*>(document);

        if (doc->document()) {
            hoedown_buffer *in = doc->document();
            hoedown_buffer *out = hoedown_buffer_new(64);

            hoedown_renderer *renderer = hoedown_html_toc_renderer_new(16);
            hoedown_markdown *markdown = hoedown_markdown_new(doc->options(), 16, renderer);

            hoedown_markdown_render(out, in->data, in->size, markdown);

            hoedown_markdown_free(markdown);
            hoedown_html_renderer_free(renderer);

            toc = QString::fromUtf8(hoedown_buffer_cstr(out));

            hoedown_buffer_free(out);
        }
    }

    return toc;
}

MarkdownConverter::ConverterOptions HoedownMarkdownConverter::supportedOptions() const
{
    return MarkdownConverter::AutolinkOption |
           MarkdownConverter::NoStrikethroughOption |
           MarkdownConverter::ExtraFootnoteOption |
           MarkdownConverter::NoSuperscriptOption;
}

unsigned long HoedownMarkdownConverter::translateConverterOptions(ConverterOptions options) const
{
    unsigned long converterOptions = HOEDOWN_EXT_FENCED_CODE | HOEDOWN_EXT_TABLES;

    // autolink
    if (options.testFlag(MarkdownConverter::AutolinkOption)) {
        converterOptions |= HOEDOWN_EXT_AUTOLINK;
    }

    // strikethrough
    if (!options.testFlag(MarkdownConverter::NoStrikethroughOption)) {
        converterOptions |= HOEDOWN_EXT_STRIKETHROUGH;
    }

//    // alphabetic lists
//    if (!options->isAlphabeticListsEnabled()) {
//        converterOptions |= MKD_NOALPHALIST;
//    }

//    // definition lists
//    if (!options->isDefinitionListsEnabled()) {
//        converterOptions |= MKD_NODLIST;
//    }

//    // SmartyPants
//    if (!options->isSmartyPantsEnabled()) {
//        converterOptions |= MKD_NOPANTS;
//    }

    // Footnotes
    if (options.testFlag(MarkdownConverter::ExtraFootnoteOption)) {
        converterOptions |= HOEDOWN_EXT_FOOTNOTES;
    }

    // Superscript
    if (!options.testFlag(MarkdownConverter::NoSuperscriptOption)) {
        converterOptions |= HOEDOWN_EXT_SUPERSCRIPT;
    }

    return converterOptions;
}
