#include "markdownparser.h"

extern "C" {
#include <markdown.h>
}

MarkdownParser::MarkdownParser()
{
}

MarkdownParser::~MarkdownParser()
{
}

QString MarkdownParser::renderAsHtml(const QString &text)
{
    QString html;

    if (text.length() > 0)
    {
        char *in = qstrdup(text.toLatin1().data());

        Document *doc = mkd_string(in, text.length(), MKD_AUTOLINK);

        mkd_compile(doc, MKD_AUTOLINK);

        char *out;
        mkd_document(doc, &out);

        html = QString::fromLocal8Bit(out);

        mkd_cleanup(doc);
    }

    return html;
}
