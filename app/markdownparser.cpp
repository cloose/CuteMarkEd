#include "markdownparser.h"

extern "C" {
#ifdef Q_OS_WIN
#include <Windows.h>
#endif
#include <mkdio.h>
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
        MMIOT *doc = mkd_string(text.toLocal8Bit().data(), text.length(), MKD_AUTOLINK | MKD_TOC);
//        MMIOT *doc = mkd_string(text.toUtf8().data(), text.length(), MKD_AUTOLINK | MKD_TOC);

        mkd_compile(doc, MKD_AUTOLINK | MKD_TOC);

        char *out;
        mkd_document(doc, &out);

        html = QString::fromLocal8Bit(out);
//        html = QString::fromUtf8(out);

        mkd_cleanup(doc);
    }

    return html;
}
