#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>

class MarkdownEditor;


class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    explicit LineNumberArea(MarkdownEditor *editor);
    
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    MarkdownEditor *editor;
};

#endif // LINENUMBERAREA_H
