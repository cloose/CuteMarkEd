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
#ifndef PARSER_H
#define PARSER_H

#include <QtCore/qstring.h>

extern "C" {
#ifdef Q_OS_WIN
#include <Windows.h>
#endif
#include <mkdio.h>
}

namespace Discount
{

class Parser
{
public:
    Parser();
    ~Parser();

    static MMIOT* parseString(const QString &text);
    static QString renderAsHtml(MMIOT *document);
    static QString generateToc(MMIOT *document);

    static void cleanup(MMIOT *document);
};

}

#endif // PARSER_H
