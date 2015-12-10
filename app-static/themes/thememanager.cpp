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
#include "thememanager.h"

#include <jsonfile.h>
#include <themes/jsonthemetranslatorfactory.h>


static const QMap<QString, QString> BUILTIN_MARKDOWN_HIGHLIGHTINGS = {
    { "Default", "default" },
    { "Solarized Light", "solarized-light" },
    { "Solarized Dark", "solarized-dark" },
    { "Clearness Dark", "clearness-dark" },
    { "Byword Dark", "byword-dark" }
};

static const QMap<QString, QString> BUILTIN_CODE_HIGHLIGHTINGS = {
    { "Default", "default" },
    { "Github", "github" },
    { "Solarized Light", "solarized_light" },
    { "Solarized Dark", "solarized_dark" }
};

static const QMap<QString, QString> BUILTIN_PREVIEW_STYLESHEETS = {
    { "Default", "qrc:/css/markdown.css" },
    { "Github", "qrc:/css/github.css" },
    { "Solarized Light", "qrc:/css/solarized-light.css" },
    { "Solarized Dark", "qrc:/css/solarized-dark.css" },
    { "Clearness", "qrc:/css/clearness.css" },
    { "Clearness Dark", "qrc:/css/clearness-dark.css" },
    { "Byword Dark", "qrc:/css/byword-dark.css" }
};

ThemeCollection ThemeManager::m_htmlPreviewThemes;


ThemeManager::ThemeManager() :
    ThemeManager(":/builtin-htmlpreview-themes.json")
{
}

ThemeManager::ThemeManager(const QString &themeFileName)
{
    JsonFile<Theme>::load(themeFileName, &m_htmlPreviewThemes);
}

Theme ThemeManager::themeByName(const QString &name) const
{
    return m_htmlPreviewThemes.theme(name);
}

QStringList ThemeManager::themeNames() const
{
    return m_htmlPreviewThemes.themeNames();
}

QString ThemeManager::markdownHighlightingPath(const Theme &theme)
{
    return BUILTIN_MARKDOWN_HIGHLIGHTINGS[theme.markdownHighlighting()];
}

QString ThemeManager::codeHighlightingPath(const Theme &theme)
{
    return BUILTIN_CODE_HIGHLIGHTINGS[theme.codeHighlighting()];
}

QString ThemeManager::previewStylesheetPath(const Theme &theme)
{
    return BUILTIN_PREVIEW_STYLESHEETS[theme.previewStylesheet()];
}
