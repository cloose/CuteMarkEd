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
#ifndef SNIPPETLISTMODEL_H
#define SNIPPETLISTMODEL_H

#include <QAbstractListModel>
#include <snippets/snippetcollection.h>
struct Snippet;


class SnippetListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SnippetListModel(QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

public slots:
    void snippetCollectionChanged(SnippetCollection::CollectionChangedType changedType, const Snippet &snippet);

private:
    QList<Snippet> snippets;
};

#endif // SNIPPETLISTMODEL_H
