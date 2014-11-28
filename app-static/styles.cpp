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

static const Style BUILTIN_DEFAULT_STYLE = Style("Default", "Default", "Default", "Default", true );
static const Style BUILTIN_GITHUB_STYLE = Style("Github", "Default", "Github", "Github", true );
static const Style BUILTIN_SOLARIZED_LIGHT_STYLE = Style("Solarized Light", "Solarized Light", "Solarized Light", "Solarized Light", true );
static const Style BUILTIN_SOLARIZED_DARK_STYLE = Style("Solarized Dark", "Solarized Dark", "Solarized Dark", "Solarized Dark", true );
static const Style BUILTIN_CLEARNESS_STYLE = Style("Clearness", "Default", "Default", "Clearness", true );
static const Style BUILTIN_CLEARNESS_DARK_STYLE = Style("Clearness Dark", "Clearness Dark", "Default", "Clearness Dark", true );
static const Style BUILTIN_BYWORD_DARK_STYLE = Style("Byword Dark", "Byword Dark", "Default", "Byword Dark", true );

static const Style DEFAULT_PRESENTATION_STYLE = Style("Default Presentation", "Default", "Default", "Default Presentation", true );
static const Style BEIGE_PRESENTATION_STYLE = Style("Beige", "Default", "Default", "Beige", true );
static const Style SKY_PRESENTATION_STYLE = Style("Sky", "Default", "Default", "Sky", true );
static const Style NIGHT_PRESENTATION_STYLE = Style("Night", "Default", "Default", "Night", true );
static const Style SERIF_PRESENTATION_STYLE = Style("Serif", "Default", "Default", "Serif", true );
static const Style SIMPLE_PRESENTATION_STYLE = Style("Simple", "Default", "Default", "Simple", true );
static const Style SOLARIZED_PRESENTATION_STYLE = Style("Solarized", "Solarized Light", "Default", "Solarized", true);


Styles::Styles() 
{
    setupBuiltinMarkdownHighlightings();
    setupBuiltinCodeHighlightings();
    setupBuiltinPreviewStylesheets();
    setupBuiltinStyles();
}

QStringList Styles::htmlPreviewStyleNames() const 
{
    return m_htmlPreviewStyles.styleNames();
}

QStringList Styles::presentationStyleNames() const
{
    return m_presentationStyles.styleNames();
}

Style Styles::style(const QString &name) const
{
    if (m_htmlPreviewStyles.styleNames().contains(name))
        return m_htmlPreviewStyles.style(name);
    else
        return m_presentationStyles.style(name);
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
    m_htmlPreviewStyles.insert(BUILTIN_DEFAULT_STYLE);
    m_htmlPreviewStyles.insert(BUILTIN_GITHUB_STYLE);
    m_htmlPreviewStyles.insert(BUILTIN_SOLARIZED_LIGHT_STYLE);
    m_htmlPreviewStyles.insert(BUILTIN_SOLARIZED_DARK_STYLE);
    m_htmlPreviewStyles.insert(BUILTIN_CLEARNESS_STYLE);
    m_htmlPreviewStyles.insert(BUILTIN_CLEARNESS_DARK_STYLE);
    m_htmlPreviewStyles.insert(BUILTIN_BYWORD_DARK_STYLE);

    m_presentationStyles.insert(DEFAULT_PRESENTATION_STYLE);
    m_presentationStyles.insert(BEIGE_PRESENTATION_STYLE);
    m_presentationStyles.insert(SKY_PRESENTATION_STYLE);
    m_presentationStyles.insert(NIGHT_PRESENTATION_STYLE);
    m_presentationStyles.insert(SERIF_PRESENTATION_STYLE);
    m_presentationStyles.insert(SIMPLE_PRESENTATION_STYLE);
    m_presentationStyles.insert(SOLARIZED_PRESENTATION_STYLE);
}

