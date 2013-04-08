#include "markdowneditor.h"

#include <QDebug>

MarkdownEditor::MarkdownEditor(QWidget *parent) :
    QPlainTextEdit(parent)
{
}

void MarkdownEditor::keyPressEvent(QKeyEvent *e)
{
    // Ctrl+Right Arrow
    if ((e->key() == Qt::Key_Right) && (e->modifiers() & Qt::ControlModifier)) {
        // move cursor to start of line
        QTextCursor cursor = textCursor();
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
                QTextDocument *doc = document();
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

        e->accept();
        return;
    }

    // Ctrl+Left Arrow
    if ((e->key() == Qt::Key_Left) && (e->modifiers() & Qt::ControlModifier)) {
        QTextCursor cursor = textCursor();
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

        e->accept();
        return;
    }

    QPlainTextEdit::keyPressEvent(e);
}
