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
#include "jsonthemetranslator.h"

namespace {

static const QLatin1String NAME("name");
static const QLatin1String MARKDOWN_HIGHLIGHTING("markdownHighlighting");
static const QLatin1String CODE_HIGHLIGHTING("codeHighlighting");
static const QLatin1String PREVIEW_STYLESHEET("previewStylesheet");

}

Theme JsonThemeTranslator::fromJsonObject(const QJsonObject &object)
{
    QString name = object.value(NAME).toString();
    QString markdownHighlighting = object.value(MARKDOWN_HIGHLIGHTING).toString();
    QString codeHighlighting = object.value(CODE_HIGHLIGHTING).toString();
    QString previewStylesheet = object.value(PREVIEW_STYLESHEET).toString();

    return { name, markdownHighlighting, codeHighlighting, previewStylesheet };
}

QJsonObject JsonThemeTranslator::toJsonObject(const Theme &theme)
{
    QJsonObject object;
    object.insert(NAME, theme.name());
    object.insert(MARKDOWN_HIGHLIGHTING, theme.markdownHighlighting());
    object.insert(CODE_HIGHLIGHTING, theme.codeHighlighting());
    object.insert(PREVIEW_STYLESHEET, theme.previewStylesheet());

    return object;
}

