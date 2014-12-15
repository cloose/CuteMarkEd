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
#include "jsonstyletranslatortest.h"

#include <QtTest>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <styles/jsonstyletranslator.h>
#include <styles/style.h>
#include <styles/stylecollection.h>


QJsonDocument NewStyleDocumentWithObject(const QJsonObject &jsonObject)
{
    QJsonArray styleArray;
    styleArray.append(jsonObject);

    QJsonObject object;
    object.insert("styles", styleArray);

    QJsonDocument doc(object);
    return doc;
}

void JsonStyleTranslatorTest::initTestCase()
{
    translator = new JsonStyleTranslator();
}

void JsonStyleTranslatorTest::translatesJsonDocumentToStyles()
{
    Style expected;
    expected.name = "name";
    expected.markdownHighlighting = "markdownHighlighting";
    expected.codeHighlighting = "codeHighlighting";
    expected.previewStylesheet = "previewStylesheet";
    expected.builtIn = true;

    QJsonObject jsonObject;
    jsonObject.insert("name", expected.name);
    jsonObject.insert("markdownHighlighting", expected.markdownHighlighting);
    jsonObject.insert("codeHighlighting", expected.codeHighlighting);
    jsonObject.insert("previewStylesheet", expected.previewStylesheet);
    jsonObject.insert("builtIn", expected.builtIn);

    QJsonDocument doc = NewStyleDocumentWithObject(jsonObject);

    StyleCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 1);
    QCOMPARE(collection.at(0).name, expected.name);
    QCOMPARE(collection.at(0).markdownHighlighting, expected.markdownHighlighting);
    QCOMPARE(collection.at(0).codeHighlighting, expected.codeHighlighting);
    QCOMPARE(collection.at(0).previewStylesheet, expected.previewStylesheet);
    QCOMPARE(collection.at(0).builtIn, expected.builtIn);
}

void JsonStyleTranslatorTest::translatesEmptyJsonDocumentToEmptyStyles()
{
    Style expected;
    expected.name = QString();
    expected.markdownHighlighting = QString();
    expected.codeHighlighting = QString();
    expected.previewStylesheet = QString();
    expected.builtIn = false;

    QJsonObject emptyJsonObject;
    QJsonDocument doc = NewStyleDocumentWithObject(emptyJsonObject);

    StyleCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 1);
    QCOMPARE(collection.at(0).name, expected.name);
    QCOMPARE(collection.at(0).markdownHighlighting, expected.markdownHighlighting);
    QCOMPARE(collection.at(0).codeHighlighting, expected.codeHighlighting);
    QCOMPARE(collection.at(0).previewStylesheet, expected.previewStylesheet);
    QCOMPARE(collection.at(0).builtIn, expected.builtIn);
}

void JsonStyleTranslatorTest::defectIfJsonDocumentIsInvalid()
{
    QJsonDocument doc;

    StyleCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(!success);
    QCOMPARE(collection.count(), 0);
}

void JsonStyleTranslatorTest::translatesStyleCollectionToJsonDocument()
{
    Style style;
    style.name = "name";
    style.markdownHighlighting = "markdownHighlighting";
    style.codeHighlighting = "codeHighlighting";
    style.previewStylesheet = "previewStylesheet";
    style.builtIn = true;

    StyleCollection collection;
    collection.insert(style);

    QJsonObject expected;
    expected.insert("name", style.name);
    expected.insert("markdownHighlighting", style.markdownHighlighting);
    expected.insert("codeHighlighting", style.codeHighlighting);
    expected.insert("previewStylesheet", style.previewStylesheet);
    expected.insert("builtIn", style.builtIn);

    QJsonDocument actual = translator->createDocument(&collection);

    QVERIFY(actual.isObject());
    QVERIFY(actual.object().contains("styles"));
    QVERIFY(actual.object().value("styles").isArray());

    QJsonObject actualObject = actual.object().value("styles").toArray().first().toObject();
    QCOMPARE(actualObject["name"], expected["name"]);
    QCOMPARE(actualObject["markdownHighlighting"], expected["markdownHighlighting"]);
    QCOMPARE(actualObject["codeHighlighting"], expected["codeHighlighting"]);
    QCOMPARE(actualObject["previewStylesheet"], expected["previewStylesheet"]);
    QCOMPARE(actualObject["builtIn"], expected["builtIn"]);
}

void JsonStyleTranslatorTest::cleanupTestCase()
{
    delete translator;
}

