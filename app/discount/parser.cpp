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

    const char *utf8Data = markdownText.toUtf8().data();
    MMIOT *doc = mkd_string(utf8Data, qstrlen(utf8Data), MKD_AUTOLINK | MKD_TOC | MKD_NOSTYLE);

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
    // generate table of contents
    char *out;
    mkd_toc(document, &out);

    return QString::fromLocal8Bit(out);
}

void Parser::cleanup(MMIOT *document)
{
    mkd_cleanup(document);
}
