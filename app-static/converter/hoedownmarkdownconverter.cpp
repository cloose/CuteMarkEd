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
#include "options.h"

class HoedownMarkdownDocument : public MarkdownDocument
{
public:
    explicit HoedownMarkdownDocument(hoedown_buffer *document) : discountDocument(document) {}
    ~HoedownMarkdownDocument() { hoedown_buffer_free(discountDocument); }

    hoedown_buffer *document() const { return discountDocument; }

private:
    hoedown_buffer *discountDocument;
};


HoedownMarkdownConverter::HoedownMarkdownConverter() :
    converterOptions(0),
    renderOptions(0)
{
}

MarkdownDocument *HoedownMarkdownConverter::createDocument(const QString &text)
{
    hoedown_buffer *doc = 0;

    if (text.length() > 0) {
        QString markdownText(text);

        // text has to always end with a line break,
        // otherwise characters are missing in HTML
        if (!markdownText.endsWith('\n')) {
            markdownText.append('\n');
        }

        QByteArray utf8Data = markdownText.toUtf8();
        doc = hoedown_buffer_new(utf8Data.length());
        hoedown_buffer_puts(doc, utf8Data.data());
//        doc->data = utf8Data.data();
    }

    return new HoedownMarkdownDocument(doc);
}

QString HoedownMarkdownConverter::renderAsHtml(MarkdownDocument *document)
{
    QString html;

    if (document) {
        HoedownMarkdownDocument *doc = dynamic_cast<HoedownMarkdownDocument*>(document);

        if (doc->document()) {
            hoedown_buffer *in = doc->document();
            hoedown_buffer *out = hoedown_buffer_new(64);

            hoedown_renderer *renderer = hoedown_html_renderer_new(renderOptions, 0);
            hoedown_markdown *markdown = hoedown_markdown_new(converterOptions, 16, renderer);

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

            hoedown_renderer *renderer = hoedown_html_toc_renderer_new(0);
            hoedown_markdown *markdown = hoedown_markdown_new(converterOptions, 16, renderer);

            hoedown_markdown_render(out, in->data, in->size, markdown);

            hoedown_markdown_free(markdown);
            hoedown_html_renderer_free(renderer);

            toc = QString::fromUtf8(hoedown_buffer_cstr(out));

            hoedown_buffer_free(out);
        }
    }

    return toc;
}

void HoedownMarkdownConverter::setConverterOptions(Options *options)
{
    renderOptions = HOEDOWN_HTML_TOC | HOEDOWN_HTML_SKIP_STYLE;

    converterOptions = HOEDOWN_EXT_FENCED_CODE | HOEDOWN_EXT_TABLES;

    // autolink
    if (options->isAutolinkEnabled()) {
        converterOptions |= HOEDOWN_EXT_AUTOLINK;
    }

    // strikethrough
    if (options->isStrikethroughEnabled()) {
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
    if (options->isFootnotesEnabled()) {
        converterOptions |= HOEDOWN_EXT_FOOTNOTES;
    }

    // Superscript
    if (!options->isSuperscriptEnabled()) {
        converterOptions |= HOEDOWN_EXT_SUPERSCRIPT;
    }
}
