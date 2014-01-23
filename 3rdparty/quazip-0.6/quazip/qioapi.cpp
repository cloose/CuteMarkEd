/* ioapi.c -- IO base function header for compress/uncompress .zip
   files using zlib + zip or unzip API

   Version 1.01e, February 12th, 2005

   Copyright (C) 1998-2005 Gilles Vollant

   Modified by Sergey A. Tachenov to integrate with Qt.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zlib.h"
#include "ioapi.h"
#include "quazip_global.h"
#include <QIODevice>


/* I've found an old Unix (a SunOS 4.1.3_U1) without all SEEK_* defined.... */

#ifndef SEEK_CUR
#define SEEK_CUR    1
#endif

#ifndef SEEK_END
#define SEEK_END    2
#endif

#ifndef SEEK_SET
#define SEEK_SET    0
#endif

voidpf call_zopen64 (const zlib_filefunc64_32_def* pfilefunc,voidpf file,int mode)
{
    if (pfilefunc->zfile_func64.zopen64_file != NULL)
        return (*(pfilefunc->zfile_func64.zopen64_file)) (pfilefunc->zfile_func64.opaque,file,mode);
    else
    {
        return (*(pfilefunc->zopen32_file))(pfilefunc->zfile_func64.opaque,file,mode);
    }
}

int call_zseek64 (const zlib_filefunc64_32_def* pfilefunc,voidpf filestream, ZPOS64_T offset, int origin)
{
    if (pfilefunc->zfile_func64.zseek64_file != NULL)
        return (*(pfilefunc->zfile_func64.zseek64_file)) (pfilefunc->zfile_func64.opaque,filestream,offset,origin);
    else
    {
        uLong offsetTruncated = (uLong)offset;
        if (offsetTruncated != offset)
            return -1;
        else
            return (*(pfilefunc->zseek32_file))(pfilefunc->zfile_func64.opaque,filestream,offsetTruncated,origin);
    }
}

ZPOS64_T call_ztell64 (const zlib_filefunc64_32_def* pfilefunc,voidpf filestream)
{
    if (pfilefunc->zfile_func64.zseek64_file != NULL)
        return (*(pfilefunc->zfile_func64.ztell64_file)) (pfilefunc->zfile_func64.opaque,filestream);
    else
    {
        uLong tell_uLong = (*(pfilefunc->ztell32_file))(pfilefunc->zfile_func64.opaque,filestream);
        if ((tell_uLong) == ((uLong)-1))
            return (ZPOS64_T)-1;
        else
            return tell_uLong;
    }
}

voidpf ZCALLBACK qiodevice_open_file_func (
   voidpf /*opaque UNUSED*/,
   voidpf file,
   int mode)
{
    QIODevice *iodevice = reinterpret_cast<QIODevice*>(file);
    if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER)==ZLIB_FILEFUNC_MODE_READ)
        iodevice->open(QIODevice::ReadOnly);
    else
    if (mode & ZLIB_FILEFUNC_MODE_EXISTING)
        iodevice->open(QIODevice::ReadWrite);
    else
    if (mode & ZLIB_FILEFUNC_MODE_CREATE)
        iodevice->open(QIODevice::WriteOnly);

    if (iodevice->isOpen()) {
        if (iodevice->isSequential()) {
            iodevice->close();
            return NULL;
        } else {
            return iodevice;
        }
    } else
        return NULL;
}


uLong ZCALLBACK qiodevice_read_file_func (
   voidpf /*opaque UNUSED*/,
   voidpf stream,
   void* buf,
   uLong size)
{
    uLong ret;
    ret = (uLong)((QIODevice*)stream)->read((char*)buf,size);
    return ret;
}


uLong ZCALLBACK qiodevice_write_file_func (
   voidpf /*opaque UNUSED*/,
   voidpf stream,
   const void* buf,
   uLong size)
{
    uLong ret;
    ret = (uLong)((QIODevice*)stream)->write((char*)buf,size);
    return ret;
}

uLong ZCALLBACK qiodevice_tell_file_func (
   voidpf /*opaque UNUSED*/,
   voidpf stream)
{
    uLong ret;
    ret = ((QIODevice*)stream)->pos();
    return ret;
}

ZPOS64_T ZCALLBACK qiodevice64_tell_file_func (
   voidpf /*opaque UNUSED*/,
   voidpf stream)
{
    qint64 ret;
    ret = ((QIODevice*)stream)->pos();
    return static_cast<ZPOS64_T>(ret);
}

int ZCALLBACK qiodevice_seek_file_func (
   voidpf /*opaque UNUSED*/,
   voidpf stream,
   uLong offset,
   int origin)
{
    uLong qiodevice_seek_result=0;
    int ret;
    switch (origin)
    {
    case ZLIB_FILEFUNC_SEEK_CUR :
        qiodevice_seek_result = ((QIODevice*)stream)->pos() + offset;
        break;
    case ZLIB_FILEFUNC_SEEK_END :
        qiodevice_seek_result = ((QIODevice*)stream)->size() - offset;
        break;
    case ZLIB_FILEFUNC_SEEK_SET :
        qiodevice_seek_result = offset;
        break;
    default:
        return -1;
    }
    ret = !((QIODevice*)stream)->seek(qiodevice_seek_result);
    return ret;
}

int ZCALLBACK qiodevice64_seek_file_func (
   voidpf /*opaque UNUSED*/,
   voidpf stream,
   ZPOS64_T offset,
   int origin)
{
    qint64 qiodevice_seek_result=0;
    int ret;
    switch (origin)
    {
    case ZLIB_FILEFUNC_SEEK_CUR :
        qiodevice_seek_result = ((QIODevice*)stream)->pos() + offset;
        break;
    case ZLIB_FILEFUNC_SEEK_END :
        qiodevice_seek_result = ((QIODevice*)stream)->size() - offset;
        break;
    case ZLIB_FILEFUNC_SEEK_SET :
        qiodevice_seek_result = offset;
        break;
    default:
        return -1;
    }
    ret = !((QIODevice*)stream)->seek(qiodevice_seek_result);
    return ret;
}

int ZCALLBACK qiodevice_close_file_func (
   voidpf /*opaque UNUSED*/,
   voidpf stream)
{
    ((QIODevice*)stream)->close();
    return 0;
}

int ZCALLBACK qiodevice_error_file_func (
   voidpf /*opaque UNUSED*/,
   voidpf /*stream UNUSED*/)
{
    // can't check for error due to the QIODevice API limitation
    return 0;
}

void fill_qiodevice_filefunc (
  zlib_filefunc_def* pzlib_filefunc_def)
{
    pzlib_filefunc_def->zopen_file = qiodevice_open_file_func;
    pzlib_filefunc_def->zread_file = qiodevice_read_file_func;
    pzlib_filefunc_def->zwrite_file = qiodevice_write_file_func;
    pzlib_filefunc_def->ztell_file = qiodevice_tell_file_func;
    pzlib_filefunc_def->zseek_file = qiodevice_seek_file_func;
    pzlib_filefunc_def->zclose_file = qiodevice_close_file_func;
    pzlib_filefunc_def->zerror_file = qiodevice_error_file_func;
    pzlib_filefunc_def->opaque = NULL;
}

void fill_qiodevice64_filefunc (
  zlib_filefunc64_def* pzlib_filefunc_def)
{
    // Open functions are the same for Qt.
    pzlib_filefunc_def->zopen64_file = qiodevice_open_file_func;
    pzlib_filefunc_def->zread_file = qiodevice_read_file_func;
    pzlib_filefunc_def->zwrite_file = qiodevice_write_file_func;
    pzlib_filefunc_def->ztell64_file = qiodevice64_tell_file_func;
    pzlib_filefunc_def->zseek64_file = qiodevice64_seek_file_func;
    pzlib_filefunc_def->zclose_file = qiodevice_close_file_func;
    pzlib_filefunc_def->zerror_file = qiodevice_error_file_func;
    pzlib_filefunc_def->opaque = NULL;
}

void fill_zlib_filefunc64_32_def_from_filefunc32(zlib_filefunc64_32_def* p_filefunc64_32,const zlib_filefunc_def* p_filefunc32)
{
    p_filefunc64_32->zfile_func64.zopen64_file = NULL;
    p_filefunc64_32->zopen32_file = p_filefunc32->zopen_file;
    p_filefunc64_32->zfile_func64.zerror_file = p_filefunc32->zerror_file;
    p_filefunc64_32->zfile_func64.zread_file = p_filefunc32->zread_file;
    p_filefunc64_32->zfile_func64.zwrite_file = p_filefunc32->zwrite_file;
    p_filefunc64_32->zfile_func64.ztell64_file = NULL;
    p_filefunc64_32->zfile_func64.zseek64_file = NULL;
    p_filefunc64_32->zfile_func64.zclose_file = p_filefunc32->zclose_file;
    p_filefunc64_32->zfile_func64.zerror_file = p_filefunc32->zerror_file;
    p_filefunc64_32->zfile_func64.opaque = p_filefunc32->opaque;
    p_filefunc64_32->zseek32_file = p_filefunc32->zseek_file;
    p_filefunc64_32->ztell32_file = p_filefunc32->ztell_file;
}
