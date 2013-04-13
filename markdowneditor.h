#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <qplaintextedit.h>

class MarkdownEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MarkdownEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;
};

#endif // MARKDOWNEDITOR_H
