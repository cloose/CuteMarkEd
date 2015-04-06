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
#include "pmhmarkdownparser.h"

#include <QString>

#include <pmh_definitions.h>
#include <pmh_parser.h>

QMap<MarkdownElement::Type, QList<MarkdownElement> > PmhMarkdownParser::parseMarkdown(const QString &text)
{
    // parse markdown and generate syntax elements
    pmh_element **elements;
    pmh_markdown_to_elements(text.toUtf8().data(), pmh_EXT_NONE, &elements);

    QMap<MarkdownElement::Type, QList<MarkdownElement> > elementMap;
    for (int i = 0; i < pmh_NUM_LANG_TYPES; i++) {
        if (elements[i] != NULL) {
            MarkdownElement::Type type = (MarkdownElement::Type)i;
            QList<MarkdownElement> list;

            pmh_element *element = elements[i];
            while (element != NULL) {
                MarkdownElement e;
                e.type = type;
                e.start = element->pos;
                e.end = element->end;
                list.append(e);
                element = element->next;
            }
            elementMap[type] = list;
        }
    }
    return elementMap;
}

