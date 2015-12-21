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
#include "stylemanagertest.h"

#include <QtTest>

#include <themes/stylemanager.h>

static const Theme defaultTheme("Default", "Default", "Default", "Default");
static const Theme githubTheme("Github", "Github", "Github", "Github");
static const Theme solarizedLightTheme("Solarized Light", "Solarized Light", "Solarized Light", "Solarized Light");
static const Theme solarizedDarkTheme("Solarized Dark", "Solarized Dark", "Solarized Dark", "Solarized Dark");
static const Theme clearnessTheme("Clearness", "Clearness", "Clearness", "Clearness");
static const Theme clearnessDarkTheme("Clearness Dark", "Clearness Dark", "Clearness Dark", "Clearness Dark");
static const Theme bywordDarkTheme("Byword Dark", "Byword Dark", "Byword Dark", "Byword Dark");

void StyleManagerTest::returnsPathForMarkdownHighlighting()
{
    StyleManager styleManager;

    QCOMPARE(styleManager.markdownHighlightingPath(defaultTheme), QLatin1String("default"));
    QCOMPARE(styleManager.markdownHighlightingPath(solarizedLightTheme), QLatin1String("solarized-light"));
    QCOMPARE(styleManager.markdownHighlightingPath(solarizedDarkTheme), QLatin1String("solarized-dark"));
    QCOMPARE(styleManager.markdownHighlightingPath(clearnessDarkTheme), QLatin1String("clearness-dark"));
    QCOMPARE(styleManager.markdownHighlightingPath(bywordDarkTheme), QLatin1String("byword-dark"));
}

void StyleManagerTest::returnsPathForCodeHighlighting()
{
    StyleManager styleManager;

    QCOMPARE(styleManager.codeHighlightingPath(defaultTheme), QLatin1String("default"));
    QCOMPARE(styleManager.codeHighlightingPath(githubTheme), QLatin1String("github"));
    QCOMPARE(styleManager.codeHighlightingPath(solarizedLightTheme), QLatin1String("solarized_light"));
    QCOMPARE(styleManager.codeHighlightingPath(solarizedDarkTheme), QLatin1String("solarized_dark"));
}

void StyleManagerTest::returnsPathForPreviewStylesheet()
{
    StyleManager styleManager;

    QCOMPARE(styleManager.previewStylesheetPath(defaultTheme), QLatin1String("qrc:/css/markdown.css"));
    QCOMPARE(styleManager.previewStylesheetPath(githubTheme), QLatin1String("qrc:/css/github.css"));
    QCOMPARE(styleManager.previewStylesheetPath(solarizedLightTheme), QLatin1String("qrc:/css/solarized-light.css"));
    QCOMPARE(styleManager.previewStylesheetPath(solarizedDarkTheme), QLatin1String("qrc:/css/solarized-dark.css"));
    QCOMPARE(styleManager.previewStylesheetPath(clearnessTheme), QLatin1String("qrc:/css/clearness.css"));
    QCOMPARE(styleManager.previewStylesheetPath(clearnessDarkTheme), QLatin1String("qrc:/css/clearness-dark.css"));
    QCOMPARE(styleManager.previewStylesheetPath(bywordDarkTheme), QLatin1String("qrc:/css/byword-dark.css"));
}

void StyleManagerTest::returnsPathForCustomPreviewStylesheet()
{
    QString expectedPath = "file:///C:/User/Test/custom.css";
    Theme customTheme("Custom", "Default", "Default", "Custom");
    StyleManager styleManager;
    
    styleManager.insertCustomPreviewStylesheet("Custom", expectedPath);

    QCOMPARE(styleManager.previewStylesheetPath(customTheme), expectedPath);
}

void StyleManagerTest::customPreviewStylesheetOverwritesBuiltin()
{
    QString expectedPath = "file:///C:/User/Test/custom.css";
    Theme customTheme("Custom", "Default", "Default", "Github");
    StyleManager styleManager;

    styleManager.insertCustomPreviewStylesheet("Github", expectedPath);

    QCOMPARE(styleManager.previewStylesheetPath(customTheme), expectedPath);
}
