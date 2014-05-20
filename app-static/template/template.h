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
#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QString>

class Template
{
public:
    enum RenderOption {
        ScrollbarSynchronization = 0x00000001,
        MathSupport              = 0x00000002,
        CodeHighlighting         = 0x00000004
    };
    Q_DECLARE_FLAGS(RenderOptions, RenderOption)

    virtual ~Template() {}

    QString codeHighlightingStyle() const { return highlightingStyle; }
    void setCodeHighlightingStyle(const QString &style) { highlightingStyle = style; }

    virtual QString render(const QString &body, RenderOptions options) const = 0;
    virtual QString exportAsHtml(const QString &header, const QString &body, RenderOptions options) const = 0;

private:
    QString highlightingStyle;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Template::RenderOptions)

#endif // TEMPLATE_H
