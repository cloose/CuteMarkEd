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
