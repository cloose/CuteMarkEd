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
#ifndef THEMECOLLECTION_H
#define THEMECOLLECTION_H

#include <QString>
#include <QStringList>
#include <jsoncollection.h>
#include "theme.h"


class ThemeCollection : public JsonCollection<Theme>
{
public:
    bool load(const QString &fileName);

    int insert(const Theme &theme);

    int count() const;
    const Theme &at(int offset) const;
    bool contains(const QString &name) const;
    const Theme theme(const QString &name) const;
    QStringList themeNames() const;

    const QString name() const;

private:
    QStringList themesIndex;
    QList<Theme> themes;
};

#endif // THEMECOLLECTION_H

