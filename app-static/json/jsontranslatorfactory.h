/*
 * Copyright 2014 Christian Loose <christian.loose@hamburg.de>
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
#ifndef JSONTRANSLATORFACTORY_H
#define JSONTRANSLATORFACTORY_H

#include "jsontranslator.h"

#include "snippets/snippet.h"
#include "snippets/jsonsnippettranslator.h"

#include "styles/style.h"
#include "styles/jsonstyletranslator.h"


template <class T>
class JsonTranslatorFactory
{
public:
    static JsonTranslator<T> *create() { return 0; }
};

template <> class JsonTranslatorFactory<Snippet>
{
public:
    static JsonTranslator<Snippet> *create()
    {
        return new JsonSnippetTranslator();
    }
};

template <> class JsonTranslatorFactory<Style>
{
public:
    static JsonTranslator<Style> *create()
    {
        return new JsonStyleTranslator();
    }
};

#endif // JSONTRANSLATOR_H


