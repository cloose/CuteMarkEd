#include "findreplacewidget.h"
#include "ui_findreplacewidget.h"

FindReplaceWidget::FindReplaceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReplaceWidget)
{
    ui->setupUi(this);
}

FindReplaceWidget::~FindReplaceWidget()
{
    delete ui;
}
