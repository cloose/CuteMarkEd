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
#ifndef SLIDELINEMAPPING_H
#define SLIDELINEMAPPING_H

#include <QMap>
#include <QString>


class SlideLineMapping
{
public:
    void build(const QString &code);

    int lineForSlide(const QPair<int, int>& slide) const;
    QPair<int, int> slideForLine(int lineNumber) const;

    QMap<int, QPair<int, int> > lineToSlide() const;
    QMap<QPair<int, int>, int> slideToLine() const;

private:
    bool isHorizontalSlideSeparator(const QStringList &lines, int lineNumber) const;
    bool isVerticalSlideSeparator(const QStringList &lines, int lineNumber) const;

    QMap<int, QPair<int, int> > m_lineToSlide;
    QMap<QPair<int, int>, int> m_slideToLine;
};

#endif // SLIDELINEMAPPING_H
