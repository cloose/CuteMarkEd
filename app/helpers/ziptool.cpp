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
#include "helpers/ziptool.h"
#include <QDir>
#include "quazip.h"
#include "quazipfile.h"


ZipTool::ZipTool()
{
}

ZipError ZipTool::extract(const QString& sourceFile, const QString& destPath)
{
    qDebug("Opening %s\n", sourceFile.toLocal8Bit().constData());


    QuaZip zip(sourceFile);
    if (!zip.open(QuaZip::mdUnzip))
    {
        qWarning("ZipTool, could not open ZIP file: %d", zip.getZipError());
        return ErrFileNotFound;
    }
    // zip.setFileNameCodec("IBM866");
    zip.setFileNameCodec("UTF-8");

    return processZip(zip, destPath);
}

ZipError ZipTool::processZip(QuaZip& zip, const QString& destPath)
{
    qDebug("%d entries\n", zip.getEntriesCount());
    qDebug("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());

    QuaZipFile zipFile(&zip);
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile())
    {
        QuaZipFileInfo info;
        if (!zip.getCurrentFileInfo(&info))
        {
            qWarning("ZipTool, could not get current file info: %d\n", zip.getZipError());
            return ErrFileInfo;
        }

        qDebug("Zip name:    %s", info.name.toLocal8Bit().constData());

        QString fileName = info.name;
        if(fileName.endsWith("/"))
        {
            if( !createDirectory(fileName, destPath) )
            {
                return ErrDirCreate;
            }
            continue;
        }

        ZipError error = extractFile(zipFile, destPath);
        if(error!=ErrNone)
        {
            return error;
        }
    }

    return ErrNone;
}

bool ZipTool::createDirectory(const QString& pathName, const QString& destPath)
{
    QString destName = QString("%1/%2").arg(destPath).arg(pathName);
    qDebug("Creating directory %s", destName.toLocal8Bit().constData());

    QDir tmpDir(destName);
    if(!tmpDir.exists(destName))
    {
        QDir dir(destPath);
        if( !dir.mkpath(pathName) )
        {
            qDebug("Unable to create directory!");
            return false;
        }
    }
    return true;
}

ZipError ZipTool::extractFile(QuaZipFile& zipFile, const QString& destPath)
{
    if( !zipFile.open(QIODevice::ReadOnly) ) return ErrFileOpen;
    QByteArray buffer = zipFile.readAll();
    zipFile.close();
    if (zipFile.getZipError() != UNZ_OK)
    {
        return ErrFileClose;
    }

    QString fileName = QString("%1/%2").arg(destPath).arg(zipFile.getActualFileName());
    qDebug("Creating file %s", fileName.toLocal8Bit().constData());

    QFile dstFile(fileName);
    if(!dstFile.open( QIODevice::WriteOnly | QIODevice::Text )) return ErrFileCreate;
    // write the data from the bytes array into the destination file
    if(dstFile.write( buffer.data() )<0 ) return ErrFileWrite;
    dstFile.close();

    return ErrNone;
}
