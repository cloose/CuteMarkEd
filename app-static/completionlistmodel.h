/*
 * Copyright 2013-2014 Christian Loose <christian.loose@hamburg.de>
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
#ifndef COMPLETIONLISTMODEL_H
#define COMPLETIONLISTMODEL_H

#include <QAbstractListModel>
#include <snippets/snippetcollection.h>
struct Snippet;


class CompletionListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CompletionListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    void setWords(const QStringList &words);

public slots:
    void snippetCollectionChanged(SnippetCollection::CollectionChangedType changedType, const Snippet &snippet);

private:
    QList<Snippet> snippets;
    QStringList words;
};

#endif // COMPLETIONLISTMODEL_H
