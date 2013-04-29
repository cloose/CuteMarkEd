#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <qplaintextedit.h>

class MarkdownHighlighter;


class MarkdownEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MarkdownEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    void loadStyleFromStylesheet(const QString &fileName);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;
    MarkdownHighlighter *highlighter;
};

#endif // MARKDOWNEDITOR_H
