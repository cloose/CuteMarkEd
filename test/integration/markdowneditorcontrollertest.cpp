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
#include "markdowneditorcontrollertest.h"

#include <QtTest>
#include <QPlainTextEdit>

#include "markdowneditorcontroller.h"

void MarkdownEditorControllerTest::initTestCase()
{
    editorView = new QPlainTextEdit();
    controller = new MarkdownEditorController(editorView);

    editorView->show();
    QTest::qWaitForWindowExposed(editorView);
    editorView->activateWindow();
    QTest::qWaitForWindowActive(editorView);
}

void MarkdownEditorControllerTest::cleanupTestCase()
{
    delete controller;
    delete editorView;
}

void MarkdownEditorControllerTest::returnsZeroWordsForEmptyText()
{
    editorView->clear();

    int wordCount = controller->countWords();

    QCOMPARE(wordCount, 0);
}

void MarkdownEditorControllerTest::returnsZeroWordsForWhitespaceOnlyText()
{
    editorView->setPlainText("   ");

    int wordCount = controller->countWords();

    QCOMPARE(wordCount, 0);
}

void MarkdownEditorControllerTest::returnsWordCountOneForSingleWord()
{
    editorView->setPlainText("word");

    int wordCount = controller->countWords();

    QCOMPARE(wordCount, 1);
}

void MarkdownEditorControllerTest::returnsWordCountForMultipleWords()
{
    editorView->setPlainText("word word word");

    int wordCount = controller->countWords();

    QCOMPARE(wordCount, 3);
}

void MarkdownEditorControllerTest::returnedWordCountIncludesNumbers()
{
    editorView->setPlainText("1. word 42");

    int wordCount = controller->countWords();

    QCOMPARE(wordCount, 3);
}

