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

    QCOMPARE(mapping.lineToSlide().count(), 1);
    QCOMPARE(mapping.slideToLine().count(), 1);
    QCOMPARE(mapping.slideForLine(expectedLineNumber), expectedSlide);
    QCOMPARE(mapping.lineForSlide(expectedSlide), expectedLineNumber);
}

void SlideLineMappingTest::horizontalSlideSeparatorMustBeSurroundedByBlankLines()
{
    SlideLineMapping mapping;
    QString markdownDocument = "Text\n---\nText";
    QPair<int, int> expectedSlide(0, 0);
    int expectedLineNumber = 1;

    mapping.build(markdownDocument);

    QCOMPARE(mapping.lineToSlide().count(), 1);
    QCOMPARE(mapping.slideToLine().count(), 1);
    QCOMPARE(mapping.slideForLine(expectedLineNumber), expectedSlide);
    QCOMPARE(mapping.lineForSlide(expectedSlide), expectedLineNumber);
}

void SlideLineMappingTest::verticalSlideSeparatorMustBeSurroundedByBlankLines()
{
    SlideLineMapping mapping;
    QString markdownDocument = "Text\n--\nText";
    QPair<int, int> expectedSlide(0, 0);
    int expectedLineNumber = 1;

    mapping.build(markdownDocument);

    QCOMPARE(mapping.lineToSlide().count(), 1);
    QCOMPARE(mapping.slideToLine().count(), 1);
    QCOMPARE(mapping.slideForLine(expectedLineNumber), expectedSlide);
    QCOMPARE(mapping.lineForSlide(expectedSlide), expectedLineNumber);
}

void SlideLineMappingTest::holdsEntryForeachSlide()
{
    SlideLineMapping mapping;
    QString markdownDocument = "Slide 1\n\n---\n\nSlide 2\n\n---\n\nSlide3";

    mapping.build(markdownDocument);

    QCOMPARE(mapping.lineToSlide().count(), 3);
    QCOMPARE(mapping.slideToLine().count(), 3);

    QCOMPARE(mapping.slideForLine(3), qMakePair(0, 0));
    QCOMPARE(mapping.slideForLine(7), qMakePair(1, 0));
    QCOMPARE(mapping.slideForLine(9), qMakePair(2, 0));
    QCOMPARE(mapping.lineForSlide(qMakePair(0, 0)), 1);
    QCOMPARE(mapping.lineForSlide(qMakePair(1, 0)), 4);
    QCOMPARE(mapping.lineForSlide(qMakePair(2, 0)), 8);
}

void SlideLineMappingTest::returnsSlideForEachLine()
{
    SlideLineMapping mapping;
    QString markdownDocument = "Slide 1\n\n---\n\nSlide 2\n---\n";

    mapping.build(markdownDocument);

    QCOMPARE(mapping.lineToSlide().count(), 2);
    QCOMPARE(mapping.slideToLine().count(), 2);

    QCOMPARE(mapping.slideForLine(1), qMakePair(0, 0));
    QCOMPARE(mapping.slideForLine(2), qMakePair(0, 0));
    QCOMPARE(mapping.slideForLine(3), qMakePair(0, 0));
    QCOMPARE(mapping.slideForLine(4), qMakePair(1, 0));
    QCOMPARE(mapping.slideForLine(5), qMakePair(1, 0));
    QCOMPARE(mapping.slideForLine(6), qMakePair(1, 0));
    QCOMPARE(mapping.slideForLine(7), qMakePair(1, 0));
    QCOMPARE(mapping.slideForLine(8), qMakePair(-1, -1));
}
