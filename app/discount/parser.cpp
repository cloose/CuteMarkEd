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
//    MMIOT *doc = mkd_string(text.toLatin1().data(), text.length(), MKD_AUTOLINK | MKD_TOC);
//    MMIOT *doc = mkd_string(text.toLocal8Bit().data(), text.length(), MKD_AUTOLINK | MKD_TOC);
    MMIOT *doc = mkd_string(text.toUtf8().data(), text.length(), MKD_AUTOLINK | MKD_TOC);

    mkd_compile(doc, MKD_AUTOLINK | MKD_TOC);

    return doc;
}

QString Parser::renderAsHtml(MMIOT *document)
{
    char *out;
    mkd_document(document, &out);

//    return QString::fromLocal8Bit(out);
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
