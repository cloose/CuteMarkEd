#include "parser.h"
using namespace Discount;

Parser::Parser()
{
}

Parser::~Parser()
{
}

MMIOT *Parser::parseString(const QString &text)
{
    QString markdownText(text);

    // text has to always end with a line break,
    // otherwise characters are missing in HTML
    if (!markdownText.endsWith('\n')) {
        markdownText.append('\n');
    }

    MMIOT *doc = mkd_string(markdownText.toUtf8().data(), markdownText.length(), MKD_AUTOLINK | MKD_TOC | MKD_NOSTYLE);

    mkd_compile(doc, MKD_AUTOLINK | MKD_TOC | MKD_NOSTYLE);

    return doc;
}

QString Parser::renderAsHtml(MMIOT *document)
{
    char *out;
    mkd_document(document, &out);

    return QString::fromUtf8(out);
}

QString Parser::generateToc(MMIOT *document)
{
    char *out;
    mkd_toc(document, &out);

    return QString::fromLocal8Bit(out);
}

void Parser::cleanup(MMIOT *document)
{
    mkd_cleanup(document);
}
