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
#include "jsonthemetranslatortest.h"

#include <QtTest>

#include <themes/jsonthemetranslator.h>
#include <themes/theme.h>
#include <themes/themecollection.h>

static const QLatin1String A_THEME_NAME("mytheme");
static const QLatin1String A_MARKDOWN_HIGHLIGHTING("default");
static const QLatin1String A_CODE_HIGHLIGHTING("monokai");
static const QLatin1String A_PREVIEW_STYLESHEET("github");


QJsonDocument NewJsonDocumentWithObject(const QJsonObject &jsonObject)
{
    QJsonArray themeArray;
    themeArray.append(jsonObject);

    QJsonObject object;
    object.insert("themes", themeArray);

    return QJsonDocument(object);
}

QJsonObject NewJsonThemeObject()
{
    QJsonObject jsonObject;
    jsonObject.insert("name", A_THEME_NAME);
    jsonObject.insert("markdownHighlighting", A_MARKDOWN_HIGHLIGHTING);
    jsonObject.insert("codeHighlighting", A_CODE_HIGHLIGHTING);
    jsonObject.insert("previewStylesheet", A_PREVIEW_STYLESHEET);
    jsonObject.insert("builtIn", true);

    return jsonObject;
}

void JsonThemeTranslatorTest::initTestCase()
{
    translator = new JsonThemeTranslator();
}

void JsonThemeTranslatorTest::cleanupTestCase()
{
    delete translator;
}

void JsonThemeTranslatorTest::doesNotProcessInvalidJsonDocument()
{
    QJsonDocument doc;

    ThemeCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(!success);
    QCOMPARE(collection.count(), 0);
}

void JsonThemeTranslatorTest::translatesEmptyJsonDocumentToEmptyThemes()
{
    QJsonObject themesObject;
    themesObject.insert("themes", QJsonArray());

    QJsonDocument doc(themesObject);

    ThemeCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 0);
}

void JsonThemeTranslatorTest::translatesJsonDocumentToThemes()
{
    QJsonDocument doc = NewJsonDocumentWithObject(NewJsonThemeObject());

    ThemeCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 1);
    QCOMPARE(collection.at(0).name(), A_THEME_NAME);
    QCOMPARE(collection.at(0).markdownHighlighting(), A_MARKDOWN_HIGHLIGHTING);
    QCOMPARE(collection.at(0).codeHighlighting(), A_CODE_HIGHLIGHTING);
    QCOMPARE(collection.at(0).previewStylesheet(), A_PREVIEW_STYLESHEET);
    QCOMPARE(collection.at(0).isBuiltIn(), true);
}

void JsonThemeTranslatorTest::translatesThemesToJsonDocument()
{
    Theme theme(A_THEME_NAME, A_MARKDOWN_HIGHLIGHTING, A_CODE_HIGHLIGHTING, A_PREVIEW_STYLESHEET, true);
    ThemeCollection collection;
    collection.insert(theme);

    QJsonDocument doc = translator->createDocument(&collection);

    QJsonObject actual = doc.object().value("themes").toArray().first().toObject();
    QCOMPARE(actual["name"].toString(), A_THEME_NAME);
    QCOMPARE(actual["markdownHighlighting"].toString(), A_MARKDOWN_HIGHLIGHTING);
    QCOMPARE(actual["codeHighlighting"].toString(), A_CODE_HIGHLIGHTING);
    QCOMPARE(actual["previewStylesheet"].toString(), A_PREVIEW_STYLESHEET);
    QCOMPARE(actual["builtIn"].toBool(), true);
}

