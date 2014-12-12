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
#include "stylecollection.h"


StyleCollection::StyleCollection() 
{
}

int StyleCollection::insert(const Style &style)
{
    stylesIndex << style.name;
    styles << style;
    return count(); 
}

void StyleCollection::update(const Style &style)
{
    styles.replace(stylesIndex.indexOf(style.name), style);
}

void StyleCollection::remove(const Style &style)
{
    styles.removeAt(stylesIndex.indexOf(style.name));
    stylesIndex.removeOne(style.name);
}

int StyleCollection::count() const
{
    return styles.count();
}

const Style &StyleCollection::at(int offset) const
{
    return styles.at(offset);
}

QStringList StyleCollection::styleNames() const
{
    return stylesIndex;
}

const QString StyleCollection::name() const
{
    return QStringLiteral("styles");
}

bool StyleCollection::contains(const QString &name) const
{
    return stylesIndex.contains(name);
}

const Style StyleCollection::style(const QString &name) const
{
    return styles.at(stylesIndex.indexOf(name));
}

