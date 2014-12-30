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
#include "dictionarytest.h"

#include <QTest>

#include <spellchecker/dictionary.h>

void DictionaryTest::returnsLanguageNameForLanguageCode()
{
    Dictionary german("de_DE", "");
    QCOMPARE(german.languageName(), QStringLiteral("Deutsch"));

    Dictionary americanEnglish("en_US", "");
// Qt 5.3 and higher uses at least CLDR v24 which introduced long/short
// names for english language variantes
#if QT_VERSION < QT_VERSION_CHECK(5, 3, 0)
    QCOMPARE(americanEnglish.languageName(), QStringLiteral("U.S. English"));
#else
    QCOMPARE(americanEnglish.languageName(), QStringLiteral("American English"));
#endif
}

void DictionaryTest::returnsCountryNameForLanguage()
{
    Dictionary german("de_DE", "");
    QCOMPARE(german.countryName(), QStringLiteral("Deutschland"));

    Dictionary americanEnglish("en_US", "");
    QCOMPARE(americanEnglish.countryName(), QStringLiteral("United States"));
}
