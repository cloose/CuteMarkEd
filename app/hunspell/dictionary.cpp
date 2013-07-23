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
#include "dictionary.h"
using hunspell::Dictionary;

#include <QLocale>

Dictionary::Dictionary()
{
}

Dictionary::Dictionary(const QString &language, const QString &filePath) :
    m_language(language),
    m_filePath(filePath)
{
}

Dictionary::Dictionary(const hunspell::Dictionary &other)
{
    m_language = other.m_language;
    m_filePath = other.m_filePath;
}

Dictionary::~Dictionary()
{
}

QString Dictionary::language() const
{
    return m_language;
}

QString Dictionary::languageName() const
{
    return QLocale::languageToString(QLocale(m_language).language());
}

QString Dictionary::countryName() const
{
    return QLocale::countryToString(QLocale(m_language).country());
}

QString Dictionary::filePath() const
{
    return m_filePath;
}

