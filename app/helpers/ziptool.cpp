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
#include "helpers/ziptool.h"
#include "quazip.h"
#include "quazipfile.h"

static bool extract(const QString & filePath, const QString & extDirPath, const QString & singleFileName = QString(""));

ZipTool::ZipTool()
{
}

bool ZipTool::extract()
{
    return ::extract("reveal.zip", "tmp");
}

static bool extract(const QString & filePath, const QString & extDirPath, const QString & singleFileName)
{
    QuaZip zip(filePath);

    qDebug("Opening %s\n", filePath.toLocal8Bit().constData());
    if (!zip.open(QuaZip::mdUnzip))
    {
        qWarning("testRead(): zip.open(): %d", zip.getZipError());
        return false;
    }

    zip.setFileNameCodec("IBM866");

    qDebug("%d entries\n", zip.getEntriesCount());
    qDebug("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());

    QuaZipFileInfo info;
    QuaZipFile file(&zip);

    QFile out;
    QString name;
    char c;
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile())
    {
        if (!zip.getCurrentFileInfo(&info))
        {
            qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
            return false;
        }

        if (!singleFileName.isEmpty())
        {
            if (!info.name.contains(singleFileName))
                continue;
        }

        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("testRead(): file.open(): %d", file.getZipError());
            return false;
        }

        name = QString("%1/%2").arg(extDirPath).arg(file.getActualFileName());

        if (file.getZipError() != UNZ_OK)
        {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return false;
        }

    //out.setFileName("out/" + name);
    out.setFileName(name);

    // this will fail if "name" contains subdirectories, but we don't mind that
    out.open(QIODevice::WriteOnly);
    // Slow like hell (on GNU/Linux at least), but it is not my fault.
    // Not ZIP/UNZIP package's fault either.
    // The slowest thing here is out.putChar(c).
    while (file.getChar(&c)) out.putChar(c);

    out.close();

    if (file.getZipError() != UNZ_OK) {
        qWarning("testRead(): file.getFileName(): %d", file.getZipError());
        return false;
    }

    if (!file.atEnd()) {
        qWarning("testRead(): read all but not EOF");
        return false;
    }

    file.close();

    if (file.getZipError() != UNZ_OK) {
        qWarning("testRead(): file.close(): %d", file.getZipError());
        return false;
    }
}

zip.close();

if (zip.getZipError() != UNZ_OK) {
    qWarning("testRead(): zip.close(): %d", zip.getZipError());
    return false;
}

return true;
}
