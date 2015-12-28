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
#include "theme.h"

Theme::Theme(const QString &name, 
             const QString &markdownHighlighting,
             const QString &codeHighlighting,
             const QString &previewStylesheet,
             bool builtIn) :
    m_name(name),
    m_markdownHighlighting(markdownHighlighting),
    m_codeHighlighting(codeHighlighting),
    m_previewStylesheet(previewStylesheet),
    m_builtIn(builtIn)
{
    checkInvariants();
}

void Theme::checkInvariants() const
{
    if (m_name.isEmpty()) {
        throw std::runtime_error("theme name must not be empty");
    }
    if (m_markdownHighlighting.isEmpty()) {
        throw std::runtime_error("markdown highlighting style must not be empty");
    }
    if (m_codeHighlighting.isEmpty()) {
        throw std::runtime_error("code highlighting style must not be empty");
    }
    if (m_previewStylesheet.isEmpty()) {
        throw std::runtime_error("preview stylesheet must not be empty");
    }
}
