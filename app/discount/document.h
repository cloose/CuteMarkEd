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
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QtCore/qstring.h>
#include "parser.h"

namespace Discount
{

class Document
{
public:
    Document(const QString &text, Parser::ParserOptions options);
    ~Document();

    QString toHtml();
    QString generateToc();

private:
    MMIOT *document;
    QString html;
    QString toc;
};

}

#endif // DOCUMENT_H
