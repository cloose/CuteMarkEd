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
        int offs = 0;
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
