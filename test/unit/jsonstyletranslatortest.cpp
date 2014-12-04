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
    //expected.description = "description";
    //expected.style = "style";
    //expected.cursorPosition = 1;
    expected.builtIn = true;

    QJsonObject jsonObject;
    jsonObject.insert("name", expected.name);
    //jsonObject.insert("description", expected.description);
    //jsonObject.insert("style", expected.style);
    //jsonObject.insert("cursor", expected.cursorPosition);
    jsonObject.insert("builtIn", expected.builtIn);

    QJsonDocument doc = NewStyleDocumentWithObject(jsonObject);

    StyleCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 1);
    QCOMPARE(collection.at(0).name, expected.name);
    //QCOMPARE(collection.at(0).description, expected.description);
    //QCOMPARE(collection.at(0).style, expected.style);
    //QCOMPARE(collection.at(0).cursorPosition, expected.cursorPosition);
    QCOMPARE(collection.at(0).builtIn, expected.builtIn);
}

void JsonStyleTranslatorTest::translatesEmptyJsonDocumentToEmptyStyles()
{
    Style expected;
    expected.name = QString();
    //expected.description = QString();
    //expected.style = QString();
    //expected.cursorPosition = 0;
    expected.builtIn = false;

    QJsonObject emptyJsonObject;
    QJsonDocument doc = NewStyleDocumentWithObject(emptyJsonObject);

    StyleCollection collection;
    bool success = translator->processDocument(doc, &collection);

    QVERIFY(success);
    QCOMPARE(collection.count(), 1);
    QCOMPARE(collection.at(0).name, expected.name);
    //QCOMPARE(collection.at(0).description, expected.description);
    //QCOMPARE(collection.at(0).style, expected.style);
    //QCOMPARE(collection.at(0).cursorPosition, expected.cursorPosition);
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
    //style.description = "description";
    //style.style = "style";
    //style.cursorPosition = 1;
    style.builtIn = true;

    StyleCollection collection;
    collection.insert(style);

    QJsonObject expected;
    expected.insert("name", style.name);
    //expected.insert("description", style.description);
    //expected.insert("style", style.style);
    //expected.insert("cursor", style.cursorPosition);
    expected.insert("builtIn", style.builtIn);

    QJsonDocument actual = translator->createDocument(&collection);

    QVERIFY(actual.isObject());
    QVERIFY(actual.object().contains("styles"));
    QVERIFY(actual.object().value("styles").isArray());

    QJsonObject actualObject = actual.object().value("styles").toArray().first().toObject();
    QCOMPARE(actualObject["name"], expected["name"]);
    //QCOMPARE(actualObject["description"], expected["description"]);
    //QCOMPARE(actualObject["style"], expected["style"]);
    //QCOMPARE(actualObject["cursorPosition"], expected["cursorPosition"]);
    QCOMPARE(actualObject["builtIn"], expected["builtIn"]);
}

void JsonStyleTranslatorTest::cleanupTestCase()
{
    delete translator;
}

