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
#include "snippetcompleter.h"

#include <QAbstractItemView>
#include <QCompleter>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QStandardItemModel>

#include "snippet.h"
#include "snippetrepository.h"


class SnippetItem : public QStandardItem
{
public:
    SnippetItem(const QString &text) :
        QStandardItem(QIcon("icon-puzzle-piece.fontawesome"), text)
    {
        QFont font("Monospace", 8);
        font.setStyleHint(QFont::TypeWriter);
        setFont(font);
    }
    virtual ~SnippetItem() {}

    QVariant data(int role) const {
        return (role == Qt::EditRole) ? editRoleData : QStandardItem::data(role);
    }

    void setData(const QVariant &value, int role) {
        if (role == Qt::EditRole) {
            editRoleData = value;
        } else {
            QStandardItem::setData(value, role);
        }
    }

private:
    QVariant editRoleData;
};


SnippetCompleter::SnippetCompleter(QPlainTextEdit *textEdit) :
    QObject(textEdit),
    editor(textEdit),
    snippetRepository(0),
    completer(new QCompleter(this)),
    popupOffset(0)
{
    completer->setWidget(textEdit);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseSensitive);

    connect(completer, SIGNAL(activated(QString)),
            this, SLOT(insertSnippet(QString)));
}

void SnippetCompleter::performCompletion()
{
    const QString completionPrefix = textUnderCursor();

    if (completionPrefix != completer->completionPrefix()) {
        completer->setCompletionPrefix(completionPrefix);
        completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
    }

    if (completer->completionCount() == 1)
        insertSnippet(completer->currentCompletion());
    else {
        QRect rect = editor->cursorRect();
        rect.setWidth(completer->popup()->sizeHintForColumn(0) +
                completer->popup()->verticalScrollBar()->sizeHint().width());
        rect.setLeft(editor->rect().left() + popupOffset);
        completer->complete(rect);
    }
}

bool SnippetCompleter::isPopupVisible() const
{
    return completer->popup()->isVisible();
}

void SnippetCompleter::hidePopup()
{
    completer->popup()->hide();
}

void SnippetCompleter::setPopupOffset(int leftOffset)
{
    popupOffset = leftOffset;
}

void SnippetCompleter::setSnippetRepository(SnippetRepository *repository)
{
    snippetRepository = repository;
    connect(snippetRepository, SIGNAL(dataChanged()),
            this, SLOT(updateModel()));
}

void SnippetCompleter::updateModel()
{
    QStandardItemModel *model = new QStandardItemModel(completer);

    foreach (Snippet snippet, snippetRepository->values()) {
        int triggerTextWidth = snippetRepository->maxTriggerLength() * -1;
        QString displayText = QString("%1 %2").arg(snippet.trigger, triggerTextWidth).arg(snippet.description);

        SnippetItem *item = new SnippetItem(displayText);
        item->setData(snippet.trigger, Qt::EditRole);
        item->setToolTip(snippet.snippet.toHtmlEscaped());

        model->appendRow(item);
    }

    model->sort(0);

    completer->setModel(model);
}


void SnippetCompleter::insertSnippet(const QString &trigger)
{
    if (!snippetRepository || !snippetRepository->contains(trigger)) {
        return;
    }

    Snippet snippet = snippetRepository->snippet(trigger);

    QTextCursor cursor = editor->textCursor();
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, completer->completionPrefix().length());

    int pos = cursor.position();

    cursor.insertText(snippet.snippet);

    // move cursor to requested position
    cursor.setPosition(pos);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, snippet.cursorPosition);

    editor->setTextCursor(cursor);
}

QString SnippetCompleter::textUnderCursor() const
{
    QTextCursor cursor = editor->textCursor();
    QTextDocument *document = editor->document();

    // empty text if cursor at start of line
    if (cursor.atBlockStart()) {
        return QString();
    }

    cursor.clearSelection();

    // move left until we find a space or reach the start of line
    do {
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
    } while(!document->characterAt(cursor.position()-1).isSpace() && !cursor.atBlockStart());

    return cursor.selectedText();
}
