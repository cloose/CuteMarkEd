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
#ifndef MARKDOWNCONVERTER_H
#define MARKDOWNCONVERTER_H

#include <QString>

class MarkdownDocument;


class MarkdownConverter
{
public:
    virtual ~MarkdownConverter() {}

    virtual MarkdownDocument *createDocument(const QString &text) = 0;
    virtual QString renderAsHtml(MarkdownDocument *document) = 0;
    virtual QString renderAsTableOfContents(MarkdownDocument *document) = 0;
};

#endif // MARKDOWNCONVERTER_H
