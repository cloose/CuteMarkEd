#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <qplaintextedit.h>

class MarkdownEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MarkdownEditor(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // MARKDOWNEDITOR_H
