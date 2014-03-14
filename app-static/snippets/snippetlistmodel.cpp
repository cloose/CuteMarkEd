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
#include "snippetlistmodel.h"

#include <QFont>
#include <QIcon>


SnippetListModel::SnippetListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int SnippetListModel::rowCount(const QModelIndex &parent) const
{
    return snippets.count();
}

QVariant SnippetListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > snippets.count())
        return QVariant();

    const Snippet snippet = snippets.at(index.row());

    switch (role) {
    case Qt::DecorationRole:
        return QIcon("fa-puzzle-piece.fontawesome");

    case Qt::DisplayRole:
        return QString("%1 %2").arg(snippet.trigger, -15).arg(snippet.description);

    case Qt::EditRole:
        return snippet.trigger;

    case Qt::ToolTipRole:
        return snippet.snippet.toHtmlEscaped();

    case Qt::FontRole:
        {
            QFont font("Monospace", 8);
            font.setStyleHint(QFont::TypeWriter);
            return font;
        }
        break;
    }

    return QVariant();
}

void SnippetListModel::snippetCollectionChanged(SnippetCollection::CollectionChangedType changedType, const Snippet &snippet)
{
    switch (changedType) {
    case SnippetCollection::ItemAdded:
        {
            QList<Snippet>::iterator it = qLowerBound(snippets.begin(), snippets.end(), snippet);
            int row = std::distance(snippets.begin(), it);
            beginInsertRows(QModelIndex(), row, row);
            snippets.insert(it, snippet);
            endInsertRows();
        }
        break;
    case SnippetCollection::ItemChanged:
        {
            int row = snippets.indexOf(snippet);
            snippets.replace(row, snippet);
        }
        break;
    case SnippetCollection::ItemDeleted:
        {
            int row = snippets.indexOf(snippet);
            beginRemoveRows(QModelIndex(), row, row);
            snippets.removeAt(row);
            endRemoveRows();
        }
        break;
    default:
        break;
    }
}
