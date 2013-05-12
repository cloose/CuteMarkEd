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
