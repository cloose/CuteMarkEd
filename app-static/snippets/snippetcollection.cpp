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
#include "snippetcollection.h"

SnippetCollection::SnippetCollection(QObject *parent) :
    QObject(parent)
{
}

void SnippetCollection::insert(const Snippet &snippet)
{
    snippets.insert(snippet.trigger, snippet);
    emit collectionChanged(SnippetCollection::ItemAdded);
}

void SnippetCollection::remove(const Snippet &snippet)
{
    snippets.remove(snippet.trigger);
    emit collectionChanged(SnippetCollection::ItemDeleted);
}
