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
#include "markdownmanipulator.h"

#include <QPlainTextEdit>
#include <QTextBlock>

MarkdownManipulator::MarkdownManipulator(QPlainTextEdit *editor)
{
    this->editor = editor;
}

void MarkdownManipulator::wrapSelectedText(const QString &tag)
{
    QTextCursor cursor = editor->textCursor();
    QTextDocument *doc = editor->document();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    if (cursor.hasSelection() &&
        doc->findBlock(start) == doc->findBlock(end)) {
        cursor.beginEditBlock();
        QString text = cursor.selectedText();
        text.prepend(tag);
        text.append(tag);
        cursor.insertText(text);
        cursor.endEditBlock();
        cursor.setPosition(start + tag.length());
        cursor.movePosition(QTextCursor::Right,
                            QTextCursor::KeepAnchor, end - start);
        editor->setTextCursor(cursor);
    } else if (!cursor.hasSelection()) {
        cursor.insertText(tag+tag);
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, tag.length());
        editor->setTextCursor(cursor);
    }
}

void MarkdownManipulator::wrapCurrentParagraph(const QString &startTag, const QString &endTag)
{
    QTextCursor cursor = editor->textCursor();
    QTextDocument *doc = editor->document();

    cursor.beginEditBlock();

    // find start of markdown paragraph
    if (cursor.blockNumber() > 0) {
        while (!cursor.atStart()) {
            cursor.movePosition(QTextCursor::PreviousBlock);

            // empty line?
            if (cursor.block().text().isEmpty()) {
                cursor.movePosition(QTextCursor::NextBlock);
                break;
            }
        }
    }

    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.insertText(startTag);

    // find end of markdown paragraph
    while (cursor.block() != doc->lastBlock()) {
        cursor.movePosition(QTextCursor::NextBlock);

        // empty line?
        if (cursor.block().text().isEmpty()) {
            cursor.movePosition(QTextCursor::PreviousBlock);
            break;
        }
    }

    cursor.movePosition(QTextCursor::EndOfBlock);
    cursor.insertText(endTag);

    cursor.endEditBlock();
}

void MarkdownManipulator::appendToLine(const QString &text)
{
    QTextCursor cursor = editor->textCursor();

    cursor.beginEditBlock();

    // append passed text to end of current line
    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.insertText(text);

    cursor.endEditBlock();
}

void MarkdownManipulator::prependToLine(const QChar &mark)
{
    QTextCursor cursor = editor->textCursor();
    QTextDocument *doc = editor->document();

    cursor.beginEditBlock();

    // move cursor to start of line
    cursor.movePosition(QTextCursor::StartOfLine);

    // search for last mark
    int pos = cursor.position();
    while (doc->characterAt(pos++) == mark)
        ;

    // insert new mark
    cursor.insertText(mark);

    // add space after mark, if missing
    if (doc->characterAt(pos) != ' ') {
        cursor.insertText(" ");
    }

    cursor.endEditBlock();
}

void MarkdownManipulator::increaseHeadingLevel()
{
    // move cursor to start of line
    QTextCursor cursor = editor->textCursor();
    cursor.beginEditBlock();
    cursor.movePosition(QTextCursor::StartOfLine);

    // search for last heading mark (#)
    int pos = cursor.position();
    while ('#' == cursor.document()->characterAt(pos++))
        ;

    if ((pos - cursor.position()) < 7) {
        cursor.insertText("#");
        if (' ' != cursor.document()->characterAt(pos)) {
            cursor.insertText(" ");
        } else {
            int pos = cursor.position();
            QTextDocument *doc = editor->document();
            while (' ' == doc->characterAt(pos))
                ++pos;
            int d = (pos - cursor.position());
            if (d > 1) {
                cursor.movePosition(QTextCursor::Right,
                                    QTextCursor::KeepAnchor, d - 1);
                cursor.removeSelectedText();
            }
        }
    }
    cursor.endEditBlock();
}

void MarkdownManipulator::decreaseHeadingLevel()
{
    QTextCursor cursor = editor->textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);

    if ('#' == cursor.document()->characterAt(cursor.position())) {
        cursor.beginEditBlock();
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
        if (' ' == cursor.document()->characterAt(cursor.position())) {
            cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
            cursor.removeSelectedText();
        }
        cursor.endEditBlock();
    }
}

void MarkdownManipulator::formatTextAsQuote()
{
    QTextCursor cursor = editor->textCursor();
    QTextDocument *doc = editor->document();

    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();

    if (cursor.hasSelection() &&
        doc->findBlock(start) != doc->findBlock(end)) {
        formatBlock('>');
    } else {
        prependToLine('>');
    }
}

void MarkdownManipulator::insertTable(int rows, int columns, const QList<Qt::Alignment> &alignments, const QList<QStringList> &cells)
{
    QTextCursor cursor = editor->textCursor();
    cursor.beginEditBlock();
    int pos = cursor.position();

    // table header
    QStringList headers = cells.at(0);

    QString header("| ");
    header.append(headers.join(" | "));
    header.append(" |");
    cursor.insertText(header);
    cursor.insertBlock();

    // separator between table header and body including alignment
    QString line("|");
    for (int col = 0; col < columns; ++col) {
        header = headers.at(col);
        QString underline(header.length()+2, QChar('-'));

        switch (alignments.at(col)) {
        case Qt::AlignCenter:
            underline.replace(0, 1, ':');
            underline.replace(underline.length()-1, 1, ':');
            break;
        case Qt::AlignRight:
            underline.replace(underline.length()-1, 1, ':');
            break;
        default:
            break;
        }

        line.append(underline);
        line.append("|");
    }
    cursor.insertText(line);
    cursor.insertBlock();

    // table body
    for (int i = 0; i < rows-1; ++i) {
        QStringList rowData = cells.at(i+1);

        QString row("| ");
        row.append(rowData.join(" | "));
        row.append(" |");

        cursor.insertText(row);
        cursor.insertBlock();
    }

    // position to first header cell
    cursor.setPosition(pos);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 2);

    cursor.endEditBlock();

    editor->setTextCursor(cursor);
}

void MarkdownManipulator::insertImageLink(const QString &alternateText, const QString &imageSource, const QString &optionalTitle)
{
    QTextCursor cursor = editor->textCursor();
    cursor.beginEditBlock();

    QString imageLink;
    if (optionalTitle.isEmpty()) {
        imageLink = QString("![%1](%2)").arg(alternateText).arg(imageSource);
    } else {
        imageLink = QString("![%1](%2 \"%3\")").arg(alternateText).arg(imageSource).arg(optionalTitle);
    }

    cursor.insertText(imageLink);

    cursor.endEditBlock();
}

void MarkdownManipulator::formatBlock(const QChar &mark)
{
    QTextCursor cursor = editor->textCursor();
    QTextDocument *doc = editor->document();

    cursor.beginEditBlock();

    int startLine = doc->findBlock(cursor.selectionStart()).blockNumber();
    int endLine = doc->findBlock(cursor.selectionEnd()).blockNumber();

    // move cursor to start of first line
    cursor.setPosition(cursor.selectionStart());
    cursor.movePosition(QTextCursor::StartOfLine);

    for (int i = startLine; i <= endLine; ++i) {
        // search for last mark
        int pos = cursor.position();
        while (doc->characterAt(pos++) == mark)
            ;

        // insert new mark
        cursor.insertText(mark);

        // add space after mark, if missing
        if (doc->characterAt(pos) != ' ') {
            cursor.insertText(" ");
        }

        cursor.movePosition(QTextCursor::NextBlock);
    }

    cursor.endEditBlock();
}
