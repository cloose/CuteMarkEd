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
#ifndef STYLECOLLECTIONTEST_H
#define STYLECOLLECTIONTEST_H

#include <QObject>
#include <styles/stylecollection.h>


class StyleCollectionTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void holdsStylesInInserationOrder();
    void canRetrieveStyleByName();
    void canCheckIfContainsStyleByName();
};

#endif // SNIPPETCOLLECTIONTEST_H

