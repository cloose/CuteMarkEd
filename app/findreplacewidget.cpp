#include "findreplacewidget.h"
#include "ui_findreplacewidget.h"

#include <QPlainTextEdit>

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

void FindReplaceWidget::setTextEdit(QPlainTextEdit *editor)
{
    textEditor = editor;
}

void FindReplaceWidget::showEvent(QShowEvent *)
{
    ui->findLineEdit->setFocus();
    ui->findLineEdit->selectAll();
}

void FindReplaceWidget::findPreviousClicked()
{
    textEditor->find(ui->findLineEdit->text(), QTextDocument::FindBackward);
}

void FindReplaceWidget::findNextClicked()
{
    textEditor->find(ui->findLineEdit->text());
}
