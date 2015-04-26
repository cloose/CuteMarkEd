/*
 * Copyright 2015 Christian Loose <christian.loose@hamburg.de>
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
#ifndef PMHMARKDOWNPARSER_H
#define PMHMARKDOWNPARSER_H

#include <QMap>
class QString;

class MarkdownElement
{
public:
    enum Type
    {
        LINK,
        AUTO_LINK_URL,
        AUTO_LINK_EMAIL,
        IMAGE,
        CODE,
        HTML,
        HTML_ENTITY,
        EMPHASIZED,
        STRONG,
        LIST_BULLET,
        LIST_ENUMERATOR,
        COMMENT,
        H1,
        H2,
        H3,
        H4,
        H5,
        H6,
        BLOCKQUOTE,
        VERBATIM,
        HTMLBLOCK,
        HRULE,
        REFERENCE,
        NOTE
    };
    
    Type type;
    unsigned long start;
    unsigned long end;
};

class PmhMarkdownParser
{
public:
    QMap<MarkdownElement::Type, QList<MarkdownElement> > parseMarkdown(const QString &text);
};

#endif // PMHMARKDOWNPARSER_H

