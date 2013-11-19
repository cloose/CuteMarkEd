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

#include <QApplication>
#include <QAbstractItemView>
#include <QCompleter>
#include <QClipboard>
#include <QScrollBar>
#include <QStandardItemModel>

#include <snippets/snippet.h>
#include <snippets/snippetcollection.h>


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


SnippetCompleter::SnippetCompleter(QWidget *parentWidget) :
    QObject(parentWidget),
    snippetCollection(0),
    completer(new QCompleter(this))
{
    completer->setWidget(parentWidget);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseSensitive);

    connect(completer, SIGNAL(activated(QString)),
            this, SLOT(insertSnippet(QString)));
}

void SnippetCompleter::performCompletion(const QString &textUnderCursor, const QRect &popupRect)
{
    const QString completionPrefix = textUnderCursor;

    if (completionPrefix != completer->completionPrefix()) {
        completer->setCompletionPrefix(completionPrefix);
        completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
    }

    if (completer->completionCount() == 1)
        insertSnippet(completer->currentCompletion());
    else {
        QRect rect = popupRect;
        rect.setWidth(completer->popup()->sizeHintForColumn(0) +
                completer->popup()->verticalScrollBar()->sizeHint().width());
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

void SnippetCompleter::setSnippetCollection(SnippetCollection *collection)
{
    snippetCollection = collection;
    connect(snippetCollection, SIGNAL(collectionChanged(SnippetCollection::CollectionChangedType)),
            this, SLOT(updateModel()));
}

void SnippetCompleter::updateModel()
{
    QStandardItemModel *model = new QStandardItemModel(completer);

    int triggerTextWidth = longestTriggerLength() * -1;

    for (int i = 0; i < snippetCollection->count(); ++i) {
        Snippet snippet = snippetCollection->snippetAt(i);

        QString displayText = QString("%1 %2").arg(snippet.trigger, triggerTextWidth).arg(snippet.description);

        SnippetItem *item = new SnippetItem(displayText);
        item->setData(snippet.trigger, Qt::EditRole);
        item->setToolTip(snippet.snippet.toHtmlEscaped());

        model->appendRow(item);
    }

    completer->setModel(model);
}

void SnippetCompleter::insertSnippet(const QString &trigger)
{
    if (!snippetCollection || !snippetCollection->contains(trigger)) {
        return;
    }

    Snippet snippet = snippetCollection->snippet(trigger);

    QString snippetContent(snippet.snippet);
    replaceClipboardVariable(snippetContent);

    emit snippetSelected(completer->completionPrefix(), snippetContent, snippet.cursorPosition);
}

void SnippetCompleter::replaceClipboardVariable(QString &snippetContent)
{
    if (snippetContent.contains("%clipboard")) {
        QClipboard *clipboard = QApplication::clipboard();
        snippetContent.replace("%clipboard", clipboard->text());
    }
}

int SnippetCompleter::longestTriggerLength() const
{
    int longestTriggerLength = 0;

    for (int i = 0; i < snippetCollection->count(); ++i) {
        Snippet snippet = snippetCollection->snippetAt(i);
        longestTriggerLength = qMax(longestTriggerLength, snippet.trigger.length());
    }

    return longestTriggerLength;
}
