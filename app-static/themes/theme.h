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
#ifndef THEME_H
#define THEME_H

#include <QString>
#include <stdexcept>


class Theme
{
public:
    Theme(const QString &name, 
          const QString &markdownHighlighting,
          const QString &codeHighlighting,
          const QString &previewStylesheet,
          bool builtIn = false);

    QString name() const { return m_name; }

    QString markdownHighlighting() const { return m_markdownHighlighting; }

    QString codeHighlighting() const { return m_codeHighlighting; }

    QString previewStylesheet() const { return m_previewStylesheet; }

    bool isBuiltIn() const { return m_builtIn; }

    bool operator<(const Theme &rhs) const
    {
        return m_name < rhs.name();
    }

    bool operator ==(const Theme &rhs) const
    {
        return m_name == rhs.name();
    }

private:
    void checkInvariants() const;

private:
    QString m_name;
    QString m_markdownHighlighting;
    QString m_codeHighlighting;
    QString m_previewStylesheet;
    bool m_builtIn;
};

#endif // THEME_H
