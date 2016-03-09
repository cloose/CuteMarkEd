#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QWidget>

class QLabel;
class QActionGroup;

class MarkdownEditor;
class ActiveLabel;

class StatusBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBarWidget(MarkdownEditor* editor);
    ~StatusBarWidget();

public slots:
    void update();
    void showLineColumn(bool enabled);

    void setHtmlAction(QAction *action);
    void setStyleActions(QActionGroup *actionGroup);

private slots:
    void cursorPositionChanged();
    void textChanged();

    void styleContextMenu(const QPoint &pos);
    void updateStyleLabel();

private:
    MarkdownEditor* m_editor;

    QLabel *m_lineColLabel;
    QLabel *m_wordCountLabel;

    QLabel *m_styleLabel;

    QActionGroup *m_styleActions;

    ActiveLabel *m_htmlLabel;
};

#endif // STATUSBARWIDGET_H
