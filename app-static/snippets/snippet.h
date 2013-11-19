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
#ifndef SNIPPET_H
#define SNIPPET_H

#include <QString>


struct Snippet
{
    QString trigger;
    QString description;
    QString snippet;
    int cursorPosition;
    bool builtIn;

    Snippet() : cursorPosition(0), builtIn(false) {}

    bool operator<(const Snippet &rhs) const
    {
        return trigger < rhs.trigger;
    }

    bool operator ==(const Snippet &rhs) const
    {
        return trigger == rhs.trigger;
    }
};

#endif // SNIPPET_H
