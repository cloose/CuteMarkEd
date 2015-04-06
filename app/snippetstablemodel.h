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
#ifndef SNIPPETSTABLEMODEL_H
#define SNIPPETSTABLEMODEL_H

#include <QAbstractTableModel>

struct Snippet;
class SnippetCollection;

class SnippetsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SnippetsTableModel(SnippetCollection *collection, QObject *parent);
    ~SnippetsTableModel() {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QModelIndex createSnippet();
    void removeSnippet(const QModelIndex &index);

private:
    void replaceSnippet(const Snippet &snippet, const QModelIndex &index);
    bool isValidTrigger(const QString &trigger);

private:
    SnippetCollection *snippetCollection;
};

#endif // SNIPPETSTABLEMODEL_H
