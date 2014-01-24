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
#include <QDir>
#include "quazip.h"
#include "quazipfile.h"

//static ZipError extract(const QString & filePath, const QString & extDirPath);

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

    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile())
    {
        QuaZipFileInfo info;
        if (!zip.getCurrentFileInfo(&info))
        {
            qWarning("ZipTool, could not get current file info: %d\n", zip.getZipError());
            return ErrFileInfo;
        }

        qDebug("Zip name:    %s", info.name.toLocal8Bit().constData());
        qDebug("Zip flags:   %d", info.flags);
        qDebug("Internal:    %d", info.internalAttr);
        qDebug("External:    %X\n", info.externalAttr);

        QString fileName = info.name;
        if(fileName.endsWith("/"))
        {
            CreateDirectory(fileName, destPath);
            continue;
        }
    }

    return ErrNone;
}

void ZipTool::CreateDirectory(const QString& pathName, const QString& destPath)
{
    QString current = QDir::currentPath();
    qDebug("In %s: ", current.toLocal8Bit().constData());
    qDebug("Creating directory %s/%s in %s", destPath.toLocal8Bit().constData(), pathName.toLocal8Bit().constData());
    QDir dir(destPath);
    if(!dir.exists())
    if( !dir.mkdir(pathName) )
    {
        qDebug("Unable to create directory!");
    }
}

#if 0
static ZipError extract(const QString & sourceFile, const QString & destPath)
{
    //char c;
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile())
    {

/*
    // set source file in archive
    QString filePath = archive.getCurrentFileName();
    QuaZipFile zFile( archive.getZipName(), filePath );
    // open the source file
    zFile.open( QIODevice::ReadOnly );
    // create a bytes array and write the file data into it
    QByteArray ba = zFile.readAll();
    // close the source file
    zFile.close();
    // set destination file
    QFile dstFile( filePath );
    // open the destination file
    dstFile.open( QIODevice::WriteOnly | QIODevice::Text );
    // write the data from the bytes array into the destination file
    dstFile.write( ba.data() );
    //close the destination file
    dstFile.close();
 */

        QuaZipFile file(&zip);
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("testRead(): file.open(): %d", file.getZipError());
            return ErrFileOpen;
        }
        continue;

        QString name = QString("%1/%2").arg(extDirPath).arg(file.getActualFileName());

        if (file.getZipError() != UNZ_OK)
        {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return ErrZipError;
        }


        int len = file.size();
        QByteArray buffer = file.readAll();

        //out.setFileName("out/" + name);
        QFile out(name);

        // this will fail if "name" contains subdirectories, but we don't mind that
        out.open(QIODevice::WriteOnly);
        // Slow like hell (on GNU/Linux at least), but it is not my fault.
        // Not ZIP/UNZIP package's fault either.
        // The slowest thing here is out.putChar(c).
//        while (file.getChar(&c)) out.putChar(c);
        out.write(buffer.constData(), len);
        out.close();

        if (file.getZipError() != UNZ_OK)
        {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return ErrFileRead;
        }

        if (!file.atEnd())
        {
            qWarning("testRead(): read all but not EOF");
            return ErrFileEof;
        }

        file.close();

        if (file.getZipError() != UNZ_OK)
        {
            qWarning("testRead(): file.close(): %d", file.getZipError());
            return ErrFileClose;
        }
    }

    zip.close();

    if (zip.getZipError() != UNZ_OK)
    {
        qWarning("testRead(): zip.close(): %d", zip.getZipError());
        return ErrFileClose;
    }

    return ErrNone;
}
#endif
