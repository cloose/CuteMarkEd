/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "findreplacewidget.h"
#include "ui_findreplacewidget.h"

#include <QMenu>
#include <QPlainTextEdit>

FindReplaceWidget::FindReplaceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReplaceWidget),
    textEditor(0),
    findCaseSensitively(false)
{
    ui->setupUi(this);

    setupFindOptionsMenu();
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
    if (!textEditor) return;

    QTextDocument::FindFlags findOptions = QTextDocument::FindBackward;
    if (findCaseSensitively) {
        findOptions |= QTextDocument::FindCaseSensitively;
    }

    textEditor->find(ui->findLineEdit->text(), findOptions);
}

void FindReplaceWidget::findNextClicked()
{
    if (!textEditor) return;

    QTextDocument::FindFlags findOptions;
    if (findCaseSensitively) {
        findOptions |= QTextDocument::FindCaseSensitively;
    }

    textEditor->find(ui->findLineEdit->text(), findOptions);
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

void FindReplaceWidget::caseSensitiveToggled(bool enabled)
{
    findCaseSensitively = enabled;
}

void FindReplaceWidget::setupFindOptionsMenu()
{
    QMenu *findOptionsMenu = new QMenu(this);

    QAction *action = findOptionsMenu->addAction("Case Sensitive");
    action->setCheckable(true);
    connect(action, SIGNAL(toggled(bool)), SLOT(caseSensitiveToggled(bool)));

    ui->findOptionToolButton->setMenu(findOptionsMenu);
    ui->findOptionToolButton->setIcon(QIcon("icon-search.fontawesome"));
}
