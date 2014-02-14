#ifndef QUAZIP_TEST_QZTEST_H
#define QUAZIP_TEST_QZTEST_H

#include <QIODevice>
#include <QString>
#include <QStringList>
#include <QTextCodec>

extern bool createTestFiles(const QStringList &fileNames, const QString
        &dir = "tmp");
extern void removeTestFiles(const QStringList &fileNames, const QString
        &dir = "tmp");
extern bool createTestArchive(const QString &zipName, 
                              const QStringList &fileNames, 
                              const QString &dir = "tmp");
extern bool createTestArchive(const QString &zipName,
                              const QStringList &fileNames,
                              QTextCodec *codec,
                              const QString &dir = "tmp");
extern bool createTestArchive(QIODevice *ioDevice,
                              const QStringList &fileNames,
                              QTextCodec *codec,
                              const QString &dir = "tmp");

#endif // QUAZIP_TEST_QZTEST_H
