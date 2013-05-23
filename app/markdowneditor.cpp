#include "markdowneditor.h"

#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QStyle>
#include <QTextBlock>

#include <controls/linenumberarea.h>
#include <peg-markdown-highlight/styleparser.h>
#include <markdownhighlighter.h>
#include "markdownmanipulator.h"


MarkdownEditor::MarkdownEditor(QWidget *parent) :
    QPlainTextEdit(parent),
    lineNumberArea(new LineNumberArea(this)),
    highlighter(new MarkdownHighlighter(this->document()))
{
    QFont font("Monospace", 10);
    font.setStyleHint(QFont::TypeWriter);

    lineNumberArea->setFont(font);
    setFont(font);

    connect(this, SIGNAL(blockCountChanged(int)),
            this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect, int)),
            this, SLOT(updateLineNumberArea(QRect, int)));

    updateLineNumberAreaWidth(0);
}

void MarkdownEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);

    int selStart = textCursor().selectionStart();
    int selEnd = textCursor().selectionEnd();

    QPalette palette = lineNumberArea->palette();
    palette.setCurrentColorGroup(QPalette::Active);

    painter.fillRect(event->rect(), palette.color(QPalette::Background));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    qreal top = blockBoundingGeometry(block).translated(contentOffset()).top();
    qreal bottom = top;

    while (block.isValid() && top <= event->rect().bottom()) {
        top = bottom;

        const qreal height = blockBoundingRect(block).height();
        bottom = top + height;

        if (block.isVisible() && bottom >= event->rect().top()) {
            painter.setPen(palette.color(QPalette::Dark));

            bool selected = (
                                (selStart < block.position() + block.length() && selEnd > block.position())
                                || (selStart == selEnd && selStart == block.position())
                            );

            if (selected) {
                painter.save();
                painter.setPen(Qt::black);
            }

            const QString number = QString::number(blockNumber + 1);
            painter.drawText(0, top, lineNumberArea->width() - 4, height, Qt::AlignRight, number);

            if (selected)
                painter.restore();
        }

        block = block.next();
        ++blockNumber;
    }
}

int MarkdownEditor::lineNumberAreaWidth()
{
    int digits = 2;
    int max = qMax(1, blockCount());
    while (max >= 100) {
        max /= 10;
        ++digits;
    }

    QFont font = lineNumberArea->font();
    const QFontMetrics linefmt(font);

    int space = 10 + linefmt.width(QLatin1Char('9')) * digits;
    return space;
}

void MarkdownEditor::resetHighlighting()
{
    highlighter->reset();
}

void MarkdownEditor::keyPressEvent(QKeyEvent *e)
{
    // Ctrl+Right Arrow
    if ((e->key() == Qt::Key_Right) && (e->modifiers() & Qt::ControlModifier)) {
        MarkdownManipulator manipulator(this);
        manipulator.increaseHeadingLevel();

        e->accept();
        return;
    }

    // Ctrl+Left Arrow
    if ((e->key() == Qt::Key_Left) && (e->modifiers() & Qt::ControlModifier)) {
        MarkdownManipulator manipulator(this);
        manipulator.decreaseHeadingLevel();

        e->accept();
        return;
    }

    QPlainTextEdit::keyPressEvent(e);
}

void MarkdownEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QStyle::visualRect(layoutDirection(), cr,
                                QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height())));
}

void MarkdownEditor::updateLineNumberAreaWidth(int newBlockCount)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void MarkdownEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void MarkdownEditor::loadStyleFromStylesheet(const QString &fileName)
{
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream ts(&f);
    QString input = ts.readAll();

    PegMarkdownHighlight::StyleParser parser(input);
    highlighter->setStyles(parser.highlightingStyles(this->font()));
    highlighter->rehighlight();
    this->setPalette(parser.editorPalette());
    this->viewport()->setPalette(this->palette());
}

int MarkdownEditor::countWords() const
{
    QString text = toPlainText();

    // empty or only whitespaces?
    if (text.trimmed().isEmpty()) {
        return 0;
    }

    int words = 0;
    bool lastWasWhitespace = false;
    bool firstCharacter = false;

    for (int i = 0; i < text.count(); ++i) {
        if (text.at(i).isSpace()) {
            if (firstCharacter && !lastWasWhitespace) {
                words++;
            }
            lastWasWhitespace = true;
        }
        else
        {
            firstCharacter = true;
            lastWasWhitespace = false;
        }
    }

    if (!lastWasWhitespace && text.count() > 0) {
        words++;
    }

    return words;
}
