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
#include "document.h"
using Discount::Document;
using Discount::Parser;

Document::Document(const QString &text) :
    document(0)
{
    if (text.length() > 0) {
        document = Parser::parseString(text, Parser::AutolinkOption | Parser::TableOfContentsOption | Parser::NoStyleOption);
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

QString Document::generateToc()
{
    if (toc.isNull() && document) {
        toc = Parser::generateToc(document);
    }

    return toc;
}
