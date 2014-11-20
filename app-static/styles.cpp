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
#include "styles.h"

static const Style BUILTIN_DEFAULT_STYLE = { "Default", "Default", "Default" };
static const Style BUILTIN_GITHUB_STYLE = { "Default", "Github", "Github" };
static const Style BUILTIN_SOLARIZED_LIGHT_STYLE = { "Solarized Light", "Solarized Light", "Solarized Light" };
static const Style BUILTIN_SOLARIZED_DARK_STYLE = { "Solarized Dark", "Solarized Dark", "Solarized Dark" };
static const Style BUILTIN_CLEARNESS_STYLE = { "Default", "Default", "Clearness" };
static const Style BUILTIN_CLEARNESS_DARK_STYLE = { "Clearness Dark", "Default", "Clearness Dark" };
static const Style BUILTIN_BYWORD_DARK_STYLE = { "Byword Dark", "Default", "Byword Dark" };

static const Style DEFAULT_PRESENTATION_STYLE = { "Default", "Default", "Default Presentation" };
static const Style BEIGE_PRESENTATION_STYLE = { "Default", "Default", "Beige" };
static const Style SKY_PRESENTATION_STYLE = { "Default", "Default", "Sky" };
static const Style NIGHT_PRESENTATION_STYLE = { "Default", "Default", "Night" };
static const Style SERIF_PRESENTATION_STYLE = { "Default", "Default", "Serif" };
static const Style SIMPLE_PRESENTATION_STYLE = { "Default", "Default", "Simple" };
static const Style SOLARIZED_PRESENTATION_STYLE = { "Solarized Light", "Default", "Solarized" };


Styles::Styles() 
{
    setupBuiltinMarkdownHighlightings();
    setupBuiltinCodeHighlightings();
    setupBuiltinPreviewStylesheets();
    setupBuiltinStyles();
}

QStringList Styles::htmlPreviewStyleNames() const 
{
    return m_htmlPreviewStylesIndex;
}

QStringList Styles::presentationStyleNames() const
{
    return m_presentationStylesIndex;
}

Style Styles::style(const QString &name) const
{
    if (m_htmlPreviewStylesIndex.contains(name))
        return m_htmlPreviewStyles[m_htmlPreviewStylesIndex.indexOf(name)];
    else
        return m_presentationStyles[m_presentationStylesIndex.indexOf(name)];
}

QStringList Styles::markdownHighlightings() const 
{
    return QStringList(m_markdownHighlightings.keys());
}

QString Styles::pathForMarkdownHighlighting(const Style &style) const
{
    return m_markdownHighlightings[style.markdownHighlighting];
}

QStringList Styles::codeHighlightings() const 
{
    return QStringList(m_codeHighlightings.keys());
}

QString Styles::pathForCodeHighlighting(const Style &style) const
{
    return m_codeHighlightings[style.codeHighlighting];
}

QStringList Styles::previewStylesheets() const 
{
    return QStringList(m_previewStylesheets.keys());
}

QString Styles::pathForPreviewStylesheet(const Style &style) const
{
    return m_previewStylesheets[style.previewStylesheet];
}

void Styles::setupBuiltinMarkdownHighlightings() 
{
    m_markdownHighlightings.insert("Default", ":/theme/default.txt");
    m_markdownHighlightings.insert("Solarized Light", ":/theme/solarized-light+.txt");
    m_markdownHighlightings.insert("Solarized Dark", ":/theme/solarized-dark+.txt");
    m_markdownHighlightings.insert("Clearness Dark", ":/theme/clearness-dark+.txt");
    m_markdownHighlightings.insert("Byword Dark", ":/theme/byword-dark.txt");
}

void Styles::setupBuiltinCodeHighlightings() 
{
    m_codeHighlightings.insert("Default", "default");
    m_codeHighlightings.insert("Github", "github");
    m_codeHighlightings.insert("Solarized Light", "solarized_light");
    m_codeHighlightings.insert("Solarized Dark", "solarized_dark");
}

void Styles::setupBuiltinPreviewStylesheets()
{
    m_previewStylesheets.insert("Default", "qrc:/css/markdown.css");
    m_previewStylesheets.insert("Github", "qrc:/css/github.css");
    m_previewStylesheets.insert("Solarized Light", "qrc:/css/solarized-light.css");
    m_previewStylesheets.insert("Solarized Dark", "qrc:/css/solarized-dark.css");
    m_previewStylesheets.insert("Clearness", "qrc:/css/clearness.css");
    m_previewStylesheets.insert("Clearness Dark", "qrc:/css/clearness-dark.css");
    m_previewStylesheets.insert("Byword Dark", "qrc:/css/byword-dark.css");

    m_previewStylesheets.insert("Default Presentation", "https://cdn.jsdelivr.net/reveal.js/2.6.2/css/theme/default.css");
    m_previewStylesheets.insert("Beige", "https://cdn.jsdelivr.net/reveal.js/2.6.2/css/theme/beige.css");
    m_previewStylesheets.insert("Sky", "https://cdn.jsdelivr.net/reveal.js/2.6.2/css/theme/sky.css");
    m_previewStylesheets.insert("Night", "https://cdn.jsdelivr.net/reveal.js/2.6.2/css/theme/night.css");
    m_previewStylesheets.insert("Serif", "https://cdn.jsdelivr.net/reveal.js/2.6.2/css/theme/serif.css");
    m_previewStylesheets.insert("Simple", "https://cdn.jsdelivr.net/reveal.js/2.6.2/css/theme/simple.css");
    m_previewStylesheets.insert("Solarized", "https://cdn.jsdelivr.net/reveal.js/2.6.2/css/theme/solarized.css");
}

void Styles::setupBuiltinStyles()
{
    m_htmlPreviewStylesIndex << "Default" << "Github" << "Solarized Light" 
                  << "Solarized Dark" << "Clearness" << "Clearness Dark" 
                  << "Byword Dark";
    m_htmlPreviewStyles << BUILTIN_DEFAULT_STYLE << BUILTIN_GITHUB_STYLE 
             << BUILTIN_SOLARIZED_LIGHT_STYLE << BUILTIN_SOLARIZED_DARK_STYLE
             << BUILTIN_CLEARNESS_STYLE << BUILTIN_CLEARNESS_DARK_STYLE
             << BUILTIN_BYWORD_DARK_STYLE;

    m_presentationStylesIndex << DEFAULT_PRESENTATION_STYLE.previewStylesheet
                              << BEIGE_PRESENTATION_STYLE.previewStylesheet
                              << SKY_PRESENTATION_STYLE.previewStylesheet
                              << NIGHT_PRESENTATION_STYLE.previewStylesheet
                              << SERIF_PRESENTATION_STYLE.previewStylesheet
                              << SIMPLE_PRESENTATION_STYLE.previewStylesheet
                              << SOLARIZED_PRESENTATION_STYLE.previewStylesheet;

    m_presentationStyles << DEFAULT_PRESENTATION_STYLE
                         << BEIGE_PRESENTATION_STYLE
                         << SKY_PRESENTATION_STYLE
                         << NIGHT_PRESENTATION_STYLE
                         << SERIF_PRESENTATION_STYLE
                         << SIMPLE_PRESENTATION_STYLE
                         << SOLARIZED_PRESENTATION_STYLE;
}

