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
#include "markdowneditorcontroller.h"

#include <QAction>
#include <QPlainTextEdit>

MarkdownEditorController::MarkdownEditorController(QPlainTextEdit *view, QObject *parent) :
    QObject(parent),
    view(view)
{
}

int MarkdownEditorController::countWords() const
{
    QStringList words = splitTextIntoWords(view->toPlainText());
    return words.count();
}

QStringList MarkdownEditorController::splitTextIntoWords(const QString &text) const
{
    return text.split(QRegExp("\\W+"), QString::SkipEmptyParts);
}
