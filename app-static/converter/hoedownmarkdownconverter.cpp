#include "hoedownmarkdownconverter.h"

extern "C" {
#include <src/html.h>
#include <src/markdown.h>
}

#include "markdowndocument.h"

class HoedownMarkdownDocument : public MarkdownDocument
{
public:
    explicit HoedownMarkdownDocument(hoedown_buffer *document) : discountDocument(document) {}
    ~HoedownMarkdownDocument() { hoedown_buffer_free(discountDocument); }

    hoedown_buffer *document() const { return discountDocument; }

private:
    hoedown_buffer *discountDocument;
};


HoedownMarkdownConverter::HoedownMarkdownConverter()
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

            hoedown_renderer *renderer = hoedown_html_renderer_new(0, 0);
            hoedown_markdown *markdown = hoedown_markdown_new(0, 16, renderer);

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

//    if (document) {
//        DiscountMarkdownDocument *doc = dynamic_cast<DiscountMarkdownDocument*>(document);

//        if (doc->document()) {
//            // generate table of contents
//            char *out;
//            mkd_toc(doc->document(), &out);

//            toc = QString::fromUtf8(out);
//        }
//    }

    return toc;
}
