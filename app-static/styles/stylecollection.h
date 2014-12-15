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
#ifndef STYLECOLLECTION_H
#define STYLECOLLECTION_H

#include <QString>
#include <QStringList>
#include "json/jsoncollection.h"
#include "style.h"


class StyleCollection : public JsonCollection<Style>
{
public:
    StyleCollection();

    int insert(const Style &style);
    void update(const Style &style);
    void remove(const Style &style);

    int count() const;
    const Style &at(int offset) const;

    QStringList styleNames() const;
    const QString name() const;
    bool contains(const QString &name) const;
    const Style style(const QString &name) const;

private:
    QStringList stylesIndex;
    QList<Style> styles;
};

#endif // STYLECOLLECTION_H

