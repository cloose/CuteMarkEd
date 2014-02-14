/*
 * Copyright 2014 Jörg Preiß <joerg.preiss@slesa.de>
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
#ifndef ZIPTOOL_H
#define ZIPTOOL_H
#include <QString>

enum ZipError
{
    ErrNone,
    ErrFileNotFound,
    ErrFileInfo,
    ErrFileOpen,
    ErrFileRead,
    ErrDirCreate,
    ErrFileCreate,
    ErrFileWrite,
    ErrZipError,
    ErrFileEof,
    ErrFileClose
};

class QuaZip;
class QuaZipFile;

class ZipTool
{
public:
    ZipTool();
    ZipError extract(const QString& sourceFile, const QString& destPath);
private:
    ZipError processZip(QuaZip& zip, const QString& destPath);
    bool createDirectory(const QString& fileName, const QString& destPath);
    ZipError extractFile(QuaZipFile& zipFile, const QString& destPath);
};

#endif // ZIPTOOL_H
