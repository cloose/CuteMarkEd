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

#include <snippets/snippet.h>
#include <snippets/snippetcollection.h>
#include <snippets/snippetlistmodel.h>


SnippetCompleter::SnippetCompleter(SnippetCollection *collection, QWidget *parentWidget) :
    QObject(parentWidget),
    snippetCollection(collection),
    completer(new QCompleter(this))
{
    completer->setWidget(parentWidget);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseSensitive);

    connect(completer, SIGNAL(activated(QString)),
            this, SLOT(insertSnippet(QString)));

    SnippetListModel *model = new SnippetListModel(completer);
    connect(collection, SIGNAL(collectionChanged(SnippetCollection::CollectionChangedType,Snippet)),
            model, SLOT(snippetCollectionChanged(SnippetCollection::CollectionChangedType,Snippet)));
    completer->setModel(model);
}

void SnippetCompleter::performCompletion(const QString &textUnderCursor, const QRect &popupRect)
{
    const QString completionPrefix = textUnderCursor;

    if (completionPrefix != completer->completionPrefix()) {
        completer->setCompletionPrefix(completionPrefix);
        completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
    }

    if (completer->completionCount() == 1) {
        insertSnippet(completer->currentCompletion());
    } else {
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

void SnippetCompleter::insertSnippet(const QString &trigger)
{
    if (!snippetCollection || !snippetCollection->contains(trigger))
        return;

    const Snippet snippet = snippetCollection->snippet(trigger);

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
