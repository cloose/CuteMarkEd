#include "findreplacewidget.h"
#include "ui_findreplacewidget.h"

#include <QPlainTextEdit>

FindReplaceWidget::FindReplaceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReplaceWidget)
{
    ui->setupUi(this);
    setFocusProxy(ui->findLineEdit);
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

void FindReplaceWidget::replaceClicked()
{
    QString oldText = ui->findLineEdit->text();
    QString newText = ui->replaceLineEdit->text();

    QTextCursor cursor = textEditor->textCursor();
    cursor.beginEditBlock();

    if (cursor.hasSelection()) {
        cursor.insertText(newText);
    }

    textEditor->find(oldText);

    cursor.endEditBlock();
}

void FindReplaceWidget::replaceAllClicked()
{
    QString oldText = ui->findLineEdit->text();
    QString newText = ui->replaceLineEdit->text();

    textEditor->moveCursor(QTextCursor::Start);
    QTextCursor cursor = textEditor->textCursor();
    cursor.beginEditBlock();

    bool found = textEditor->find(oldText);
    while (found) {
        QTextCursor tc = textEditor->textCursor();
        if (tc.hasSelection()) {
            tc.insertText(newText);
        }
        found = textEditor->find(oldText);
    }

    cursor.endEditBlock();
}
