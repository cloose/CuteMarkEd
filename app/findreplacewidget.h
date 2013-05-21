#ifndef FINDREPLACEWIDGET_H
#define FINDREPLACEWIDGET_H

#include <QWidget>

namespace Ui {
class FindReplaceWidget;
}
class QPlainTextEdit;

class FindReplaceWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FindReplaceWidget(QWidget *parent = 0);
    ~FindReplaceWidget();
    
    void setTextEdit(QPlainTextEdit *editor);

protected:
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

private slots:
    void findPreviousClicked();
    void findNextClicked();

private:
    Ui::FindReplaceWidget *ui;
    QPlainTextEdit *textEditor;
};

#endif // FINDREPLACEWIDGET_H
