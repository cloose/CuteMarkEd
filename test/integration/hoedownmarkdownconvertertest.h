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
#ifndef HOEDOWNMARKDOWNCONVERTERTEST_H
#define HOEDOWNMARKDOWNCONVERTERTEST_H

#include <QObject>

class HoedownMarkdownConverter;


class HoedownMarkdownConverterTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void convertsEmptyStringToEmptyHtml();
    void convertsMarkdownParagraphToHtml();
    void preservesGermanUmlautsInHtml();

    void supportsSuperscriptIfEnabled();
    void ignoresSuperscriptIfDisabled();

    void benchmark_data();
    void benchmark();
    void benchmarkTableOfContents_data();
    void benchmarkTableOfContents();

    void cleanupTestCase();

private:
    HoedownMarkdownConverter *converter;
};

#endif // HOEDOWNMARKDOWNCONVERTERTEST_H
