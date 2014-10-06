/*
 * Copyright 2014 Andreas Reischuck <https://github.com/arBmind>
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
#include "slidelinemapping.h"

#include <QRegularExpression>

void SlideLineMapping::build(const QString &code)
{
    static const QRegularExpression re("\n|\r\n|\r");
    static const QString horizontalMarker("---");
    static const QString verticalMarker("--");

    m_lineToSlide.clear();
    m_slideToLine.clear();
    int horizontal = 0;
    int vertical = 0;
    int lineNumber = 0;

    QStringList lines = code.split(re);
    m_slideToLine.insert(qMakePair(horizontal, vertical), lineNumber+1);
    foreach (const QString &line, lines) {
        ++lineNumber;
        if (line == horizontalMarker) {
            m_lineToSlide.insert(lineNumber, qMakePair(horizontal, vertical));
            horizontal++;
            vertical = 0;
            m_slideToLine.insert(qMakePair(horizontal, vertical), lineNumber+1);
        }
        if (line == verticalMarker) {
            m_lineToSlide.insert(lineNumber, qMakePair(horizontal, vertical));
            vertical++;
            m_slideToLine.insert(qMakePair(horizontal, vertical), lineNumber+1);
        }
    }
    m_lineToSlide.insert(lineNumber, qMakePair(horizontal, vertical));
}


QMap<int, QPair<int, int> > SlideLineMapping::lineToSlide() const
{
    return m_lineToSlide;
}

QMap<QPair<int, int>, int> SlideLineMapping::slideToLine() const
{
    return m_slideToLine;
}

