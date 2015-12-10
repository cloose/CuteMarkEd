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
#include "thememanagertest.h"

#include <QtTest>

#include <themes/thememanager.h>

static const Theme defaultTheme("Default", "Default", "Default", "Default");
static const Theme githubTheme("Github", "Github", "Github", "Github");
static const Theme solarizedLightTheme("Solarized Light", "Solarized Light", "Solarized Light", "Solarized Light");
static const Theme solarizedDarkTheme("Solarized Dark", "Solarized Dark", "Solarized Dark", "Solarized Dark");
static const Theme clearnessTheme("Clearness", "Clearness", "Clearness", "Clearness");
static const Theme clearnessDarkTheme("Clearness Dark", "Clearness Dark", "Clearness Dark", "Clearness Dark");
static const Theme bywordDarkTheme("Byword Dark", "Byword Dark", "Byword Dark", "Byword Dark");

void ThemeManagerTest::returnsPathForMarkdownHighlighting()
{
    ThemeManager themeManager;

    QCOMPARE(themeManager.markdownHighlightingPath(defaultTheme), QLatin1String("default"));
    QCOMPARE(themeManager.markdownHighlightingPath(solarizedLightTheme), QLatin1String("solarized-light"));
    QCOMPARE(themeManager.markdownHighlightingPath(solarizedDarkTheme), QLatin1String("solarized-dark"));
    QCOMPARE(themeManager.markdownHighlightingPath(clearnessDarkTheme), QLatin1String("clearness-dark"));
    QCOMPARE(themeManager.markdownHighlightingPath(bywordDarkTheme), QLatin1String("byword-dark"));
}

void ThemeManagerTest::returnsPathForCodeHighlighting()
{
    ThemeManager themeManager;

    QCOMPARE(themeManager.codeHighlightingPath(defaultTheme), QLatin1String("default"));
    QCOMPARE(themeManager.codeHighlightingPath(githubTheme), QLatin1String("github"));
    QCOMPARE(themeManager.codeHighlightingPath(solarizedLightTheme), QLatin1String("solarized_light"));
    QCOMPARE(themeManager.codeHighlightingPath(solarizedDarkTheme), QLatin1String("solarized_dark"));
}

void ThemeManagerTest::returnsPathForPreviewStylesheet()
{
    ThemeManager themeManager;

    QCOMPARE(themeManager.previewStylesheetPath(defaultTheme), QLatin1String("qrc:/css/markdown.css"));
    QCOMPARE(themeManager.previewStylesheetPath(githubTheme), QLatin1String("qrc:/css/github.css"));
    QCOMPARE(themeManager.previewStylesheetPath(solarizedLightTheme), QLatin1String("qrc:/css/solarized-light.css"));
    QCOMPARE(themeManager.previewStylesheetPath(solarizedDarkTheme), QLatin1String("qrc:/css/solarized-dark.css"));
    QCOMPARE(themeManager.previewStylesheetPath(clearnessTheme), QLatin1String("qrc:/css/clearness.css"));
    QCOMPARE(themeManager.previewStylesheetPath(clearnessDarkTheme), QLatin1String("qrc:/css/clearness-dark.css"));
    QCOMPARE(themeManager.previewStylesheetPath(bywordDarkTheme), QLatin1String("qrc:/css/byword-dark.css"));
}

