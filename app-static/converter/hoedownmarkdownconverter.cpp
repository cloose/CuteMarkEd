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
#include "hoedownmarkdownconverter.h"

extern "C" {
#ifdef Q_OS_WIN
#include <src/html.h>
#include <src/markdown.h>
#else
#include <hoedown/html.h>
#include <hoedown/markdown.h>
#endif
}

#include "markdowndocument.h"
#include "template/htmltemplate.h"

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

        if (doc && doc->document()) {
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

Template *HoedownMarkdownConverter::templateRenderer() const
{
    static HtmlTemplate htmlTemplate;
    return &htmlTemplate;
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
