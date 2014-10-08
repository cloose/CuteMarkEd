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
#include "slidelinemappingtest.h"

#include <QTest>

#include <slidelinemapping.h>

void SlideLineMappingTest::holdsSingleEntryForEmptyDocuments()
{
    SlideLineMapping mapping;
    QString markdownDocument = "";
    QPair<int, int> expectedSlide(0, 0);
    int expectedLineNumber = 1;

    mapping.build(markdownDocument);

    QVERIFY(mapping.lineToSlide().count() == 1);
    QVERIFY(mapping.slideToLine().count() == 1);
    QCOMPARE(mapping.lineToSlide().value(expectedLineNumber), expectedSlide);
    QCOMPARE(mapping.slideToLine().value(expectedSlide), expectedLineNumber);
}

void SlideLineMappingTest::holdsEntryForeachSlide()
{
    SlideLineMapping mapping;
    QString markdownDocument = "Slide 1\n---\nSlide 2\n---\nSlide3";

    mapping.build(markdownDocument);

    QVERIFY(mapping.lineToSlide().count() == 3);
    QVERIFY(mapping.slideToLine().count() == 3);

    QCOMPARE(mapping.lineToSlide().value(2), qMakePair(0, 0));
    QCOMPARE(mapping.lineToSlide().value(4), qMakePair(1, 0));
    QCOMPARE(mapping.lineToSlide().value(5), qMakePair(2, 0));
    QCOMPARE(mapping.slideToLine().value(qMakePair(0, 0)), 1);
    QCOMPARE(mapping.slideToLine().value(qMakePair(1, 0)), 3);
    QCOMPARE(mapping.slideToLine().value(qMakePair(2, 0)), 5);
}
