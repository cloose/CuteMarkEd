/*
 * Copyright 2013-2015 Christian Loose <christian.loose@hamburg.de>
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
#include "snippetstablemodel.h"

#include <QMessageBox>

#include <snippets/snippetcollection.h>

SnippetsTableModel::SnippetsTableModel(SnippetCollection *collection, QObject *parent) :
    QAbstractTableModel(parent),
    snippetCollection(collection)
{
}

int SnippetsTableModel::rowCount(const QModelIndex &) const
{
    return snippetCollection->count();
}

int SnippetsTableModel::columnCount(const QModelIndex &) const
{
    return 2;
}

Qt::ItemFlags SnippetsTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags itemFlags = QAbstractTableModel::flags(index);
    if (index.isValid()) {
        const Snippet snippet = snippetCollection->at(index.row());
        if (!snippet.builtIn) {
            itemFlags |= Qt::ItemIsEditable;
        }
    }
    return itemFlags;
}

QVariant SnippetsTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    const Snippet snippet = snippetCollection->at(index.row());

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return snippet.trigger;
        } else {
            return snippet.description + (snippet.builtIn ? " (built-in)" : "");
        }
    }

    if (role == Qt::EditRole) {
        if (index.column() == 0) {
            return snippet.trigger;
        } else {
            return snippet.description;
        }
    }

    return QVariant();
}

bool SnippetsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    Snippet snippet = snippetCollection->at(index.row());

    if (index.column() == 0) {
        const QString &s = value.toString();
        if (!isValidTrigger(s)) {
            QMessageBox::critical(0, tr("Error", "Title of error message box"), tr("Not a valid trigger."));
            if (snippet.trigger.isEmpty())
                removeSnippet(index);
            return false;
        }
        snippet.trigger = s;
    } else {
        snippet.description = value.toString();
    }

    replaceSnippet(snippet, index);
    return true;
}

QVariant SnippetsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    if (section == 0)
         return tr("Trigger");
     else
        return tr("Description");
}

QModelIndex SnippetsTableModel::createSnippet()
{
    Snippet snippet;
    beginInsertRows(QModelIndex(), 0, 0);
    int row = snippetCollection->insert(snippet);
    endInsertRows();

    return index(row, 0);
}

void SnippetsTableModel::removeSnippet(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    Snippet snippet = snippetCollection->at(index.row());
    snippetCollection->remove(snippet);
    endRemoveRows();
}

void SnippetsTableModel::replaceSnippet(const Snippet &snippet, const QModelIndex &index)
{
    const int row = index.row();

    Snippet previousSnippet = snippetCollection->at(index.row());
    snippetCollection->remove(previousSnippet);

    int insertedRow = snippetCollection->insert(snippet);

    if (index.row() == insertedRow) {
        if (index.column() == 0)
            emit dataChanged(index, index.sibling(row, 1));
        else
            emit dataChanged(index.sibling(row, 0), index);
    } else {
        if (row < insertedRow)
            beginMoveRows(QModelIndex(), row, row, QModelIndex(), insertedRow+1);
        else
            beginMoveRows(QModelIndex(), row, row, QModelIndex(), insertedRow);
        endMoveRows();
    }
}

bool SnippetsTableModel::isValidTrigger(const QString &trigger)
{
    if (trigger.isEmpty())
        return false;

    if (snippetCollection->contains(trigger))
        return false;

    for (int i = 0; i < trigger.length(); ++i) {
        if (trigger.at(i).isSpace()) {
            return false;
        }
    }

    return true;
}

