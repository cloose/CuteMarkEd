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
#include "jsonstyletranslator.h"

#include "style.h"

namespace {

static const QLatin1String NAME("name");
static const QLatin1String MARKDOWN_HIGHLIGHTING("markdownHighlighting");
static const QLatin1String CODE_HIGHLIGHTING("codeHighlighting");
static const QLatin1String PREVIEW_STYLESHEET("previewStylesheet");
static const QLatin1String BUILTIN("builtIn");

}

Style JsonStyleTranslator::fromJsonObject(const QJsonObject &object)
{
    Style style;

    style.name = object.value(NAME).toString();
    style.markdownHighlighting = object.value(MARKDOWN_HIGHLIGHTING).toString();
    style.codeHighlighting = object.value(CODE_HIGHLIGHTING).toString();
    style.previewStylesheet = object.value(PREVIEW_STYLESHEET).toString();
    style.builtIn = object.value(BUILTIN).toBool();

    return style;
}

QJsonObject JsonStyleTranslator::toJsonObject(const Style &style)
{
    QJsonObject object;

    object.insert(NAME, style.name);
    object.insert(MARKDOWN_HIGHLIGHTING, style.markdownHighlighting);
    object.insert(CODE_HIGHLIGHTING, style.codeHighlighting);
    object.insert(PREVIEW_STYLESHEET, style.previewStylesheet);
    object.insert(BUILTIN, style.builtIn);

    return object;
}

