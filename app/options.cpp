/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
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
#include "options.h"
#include <QSettings>

Options::Options(QObject *parent) :
    QObject(parent)
{
}

QFont Options::editorFont() const
{
    return font;
}

void Options::setEditorFont(const QFont &font)
{
    this->font = font;
    emit editorFontChanged(font);
}

void Options::readSettings()
{
    QSettings settings;
    QString fontFamily = settings.value("editor/font/family", "Monospace").toString();
    int fontSize = settings.value("editor/font/size", 10).toInt();

    QFont f(fontFamily, fontSize);
    f.setStyleHint(QFont::TypeWriter);
    setEditorFont(f);
}

void Options::writeSettings()
{
    QSettings settings;
    settings.setValue("editor/font/family", font.family());
    settings.setValue("editor/font/size", font.pointSize());
}
