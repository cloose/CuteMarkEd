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
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QtCore/qmetatype.h>
#include <QtCore/qstring.h>

class Dictionary
{
public:
    Dictionary();
    Dictionary(const QString &language, const QString &filePath);
    Dictionary(const Dictionary &other);
    ~Dictionary();

    QString language() const;
    QString languageName() const;

    QString countryName() const;

    QString filePath() const;

private:
    QString m_language;
    QString m_filePath;
};

Q_DECLARE_METATYPE(Dictionary);

#endif // DICTIONARY_H
