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
#ifndef STYLES_H
#define STYLES_H

#include <QMap>
#include <QString>
#include <QStringList>

#include "styles/style.h"
#include "styles/stylecollection.h"


class Styles
{
public:
    Styles();

    QStringList htmlPreviewStyleNames() const;
    QStringList presentationStyleNames() const;
    Style style(const QString &name) const;

    QStringList markdownHighlightings() const;
    QString pathForMarkdownHighlighting(const Style &style) const;

    QStringList codeHighlightings() const;
    QString pathForCodeHighlighting(const Style &style) const;

    QStringList previewStylesheets() const;
    QString pathForPreviewStylesheet(const Style &style) const;

private:
    void setupBuiltinMarkdownHighlightings();
    void setupBuiltinCodeHighlightings();
    void setupBuiltinPreviewStylesheets();
    void setupBuiltinStyles();

    QMap<QString, QString> m_markdownHighlightings;
    QMap<QString, QString> m_codeHighlightings;
    QMap<QString, QString> m_previewStylesheets;
    StyleCollection m_htmlPreviewStyles;
    StyleCollection m_presentationStyles;
};

#endif // STYLES_H
