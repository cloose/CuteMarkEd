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

#include <QSharedPointer>
#include <json/jsonfile.h>

static const Style BUILTIN_DEFAULT_STYLE = Style("Default", "Default", "Default", "Default", true );
static const Style DEFAULT_PRESENTATION_STYLE = Style("Default Presentation", "Default", "Default", "Default Presentation", true );

QMap<QString, QString> Styles::m_markdownHighlightings;
QMap<QString, QString> Styles::m_codeHighlightings;
QMap<QString, QString> Styles::m_previewStylesheets;
QSharedPointer<StyleCollection> Styles::m_htmlPreviewStyles;
QSharedPointer<StyleCollection> Styles::m_presentationStyles;

Styles::Styles() 
{
    if (m_htmlPreviewStyles.isNull()) {
        setupBuiltinMarkdownHighlightings();
        setupBuiltinCodeHighlightings();
        setupBuiltinPreviewStylesheets();
        setupBuiltinStyles();
    }
}

QStringList Styles::htmlPreviewStyleNames() const 
{
    return m_htmlPreviewStyles->styleNames();
}

QStringList Styles::presentationStyleNames() const
{
    return m_presentationStyles->styleNames();
}

Style Styles::style(const QString &name) const
{
    if (m_htmlPreviewStyles->contains(name))
        return m_htmlPreviewStyles->style(name);
    else
        return m_presentationStyles->style(name);
}

void Styles::addHtmlPreviewStyle(const Style &style)
{
    m_htmlPreviewStyles->insert(style);
}

void Styles::updateHtmlPreviewStyle(const Style &style)
{
    m_htmlPreviewStyles->update(style);
}

void Styles::removeHtmlPreviewStyle(const QString &styleName)
{
    Style style = this->style(styleName);
    m_htmlPreviewStyles->remove(style);
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

QSharedPointer<StyleCollection> Styles::htmlPreviewStyles() const
{
    return m_htmlPreviewStyles;
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
    m_htmlPreviewStyles = QSharedPointer<StyleCollection>::create();
    if (!JsonFile<Style>::load(":/builtin-htmlpreview-styles.json", m_htmlPreviewStyles.data())) {
        m_htmlPreviewStyles->insert(BUILTIN_DEFAULT_STYLE);
    }

    m_presentationStyles = QSharedPointer<StyleCollection>::create();
    if (!JsonFile<Style>::load(":/builtin-presentation-styles.json", m_presentationStyles.data())) {
        m_presentationStyles->insert(DEFAULT_PRESENTATION_STYLE);
    }
}

