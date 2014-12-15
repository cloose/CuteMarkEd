/*
 * Copyright 2014 Christian Loose <christian.loose@hamburg.de>
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
#ifndef STYLE_H
#define STYLE_H

#include <QString>


struct Style
{
    QString name;
    QString markdownHighlighting;
    QString codeHighlighting;
    QString previewStylesheet;
    bool builtIn;

    Style() : builtIn(false) {}
    Style(const QString &styleName,
          const QString &markdown,
          const QString &code,
          const QString &preview,
          bool b) : 
        name(styleName), 
        markdownHighlighting(markdown),
        codeHighlighting(code),
        previewStylesheet(preview),
        builtIn(b) 
    {
    }

    bool operator==(const Style &rhs) const
    {
        return name == rhs.name;
    }
};

#endif // STYLE_H

