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
#ifndef JSONTHEMETRANSLATORTEST_H
#define JSONTHEMETRANSLATORTEST_H

#include <QObject>
class JsonThemeTranslator;


class JsonThemeTranslatorTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void doesNotProcessInvalidJsonDocument();
    void translatesEmptyJsonDocumentToEmptyThemes();
    void translatesJsonDocumentToThemes();
    void translatesThemesToJsonDocument();

private:
    JsonThemeTranslator *translator;
};

#endif // JSONTHEMETRANSLATORTEST_H



