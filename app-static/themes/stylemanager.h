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
#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QMap>
#include <QString>
#include "theme.h"


class StyleManager
{
public:
    void insertCustomPreviewStylesheet(const QString &styleName, const QString &stylePath);

    static QString markdownHighlightingPath(const Theme &theme);
    static QString codeHighlightingPath(const Theme &theme);
    static QString previewStylesheetPath(const Theme &theme);

private:
    static QMap<QString, QString> customPreviewStylesheets;
};

#endif // STYLEMANAGER_H

