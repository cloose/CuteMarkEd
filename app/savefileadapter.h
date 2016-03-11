/*
 * Copyright 2016 Christian Loose <christian.loose@hamburg.de>
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
#ifndef SAVEFILEADAPTER_H
#define SAVEFILEADAPTER_H

#include <QSaveFile>


class SaveFileAdapter : public QSaveFile
{
public:
    SaveFileAdapter(const QString &name) :
        QSaveFile(name)
    {
    }

    void close() {
        // IGNORE - work-around for the problem that QTextDocumentWriter::write()
        // calls close() on the device
    }

};

#endif // SAVEFILEADAPTER_H
