#include "linenumberarea.h"

#include "markdowneditor.h"


LineNumberArea::LineNumberArea(MarkdownEditor *editor) :
    QWidget(editor)
{
    this->editor = editor;
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(editor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    editor->lineNumberAreaPaintEvent(event);
}
