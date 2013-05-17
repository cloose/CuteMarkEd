#ifndef FINDREPLACEWIDGET_H
#define FINDREPLACEWIDGET_H

#include <QWidget>

namespace Ui {
class FindReplaceWidget;
}

class FindReplaceWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FindReplaceWidget(QWidget *parent = 0);
    ~FindReplaceWidget();
    
private:
    Ui::FindReplaceWidget *ui;
};

#endif // FINDREPLACEWIDGET_H
