#include "document.h"
using Discount::Document;
using Discount::Parser;

Document::Document(const QString &text) :
    document(0)
{
    if (text.length() > 0) {
        document = Parser::parseString(text);
    }
}

Document::~Document()
{
    Parser::cleanup(document);
}

QString Document::toHtml()
{
    if (html.isNull() && document) {
        html = Parser::renderAsHtml(document);
    }

    return html;
}
