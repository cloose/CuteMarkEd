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


Styles::Styles() 
{
    setupBuiltinMarkdownHighlightings();
    setupBuiltinCodeHighlightings();
    setupBuiltinPreviewStylesheets();
    setupBuiltinStyles();
}

Style Styles::style(const QString &name) const
{
    return m_styles[name];
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
}

#include <QDebug>
void Styles::setupBuiltinStyles()
{
    Style defaultStyle = { "Default", "Default", "Default" };
    m_styles.insert("Default", defaultStyle);

    Style githubStyle = { "Default", "Github", "Github" };
    m_styles.insert("Github", githubStyle);

    Style solarizedLightStyle = { "Solarized Light", "Solarized Light", "Solarized Light" };
    m_styles.insert("Solarized Light", solarizedLightStyle);

    Style solarizedDarkStyle = { "Solarized Dark", "Solarized Dark", "Solarized Dark" };
    m_styles.insert("Solarized Dark", solarizedDarkStyle);

    Style clearnessStyle = { "Default", "Default", "Clearness" };
    m_styles.insert("Clearness", clearnessStyle);

    Style clearnessDarkStyle = { "Clearness Dark", "Default", "Clearness Dark" };
    m_styles.insert("Clearness Dark", clearnessDarkStyle);

    Style bywordDarkStyle = { "Byword Dark", "Default", "Byword Dark" };
    m_styles.insert("Byword Dark", bywordDarkStyle);
    qDebug() << m_styles;
}

QDebug operator<<(QDebug dbg, const Style &s)
{
    dbg << s.markdownHighlighting << s.codeHighlighting << s.previewStylesheet;
    return dbg.space();
}
