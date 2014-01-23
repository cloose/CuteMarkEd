#include "testquazip.h"

#include "qztest.h"

#include <QDataStream>
#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QTextCodec>

#include <QtTest/QtTest>

#include <quazip/quazip.h>
#include <quazip/JlCompress.h>

void TestQuaZip::getFileList_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::newRow("simple") << "qzfilelist.zip" << (
            QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt");
    QTest::newRow("russian") << QString::fromUtf8("файл.zip") << (
        QStringList() << QString::fromUtf8("test0.txt") << QString::fromUtf8("test1/test1.txt")
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt");
    QTest::newRow("japanese") << QString::fromUtf8("テスト.zip") << (
        QStringList() << QString::fromUtf8("test.txt"));
    QTest::newRow("hebrew") << QString::fromUtf8("פתח תקווה.zip") << (
        QStringList() << QString::fromUtf8("test.txt"));
}

void TestQuaZip::getFileList()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    qSort(fileNames);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Can't create test file");
    }
    if (!createTestArchive(zipName, fileNames)) {
        QFAIL("Can't create test archive");
    }
    QuaZip testZip(zipName);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    QVERIFY(testZip.goToFirstFile());
    QString firstFile = testZip.getCurrentFileName();
    QStringList fileList = testZip.getFileNameList();
    qSort(fileList);
    QCOMPARE(fileList, fileNames);
    QHash<QString, QFileInfo> srcInfo;
    foreach (QString fileName, fileNames) {
        srcInfo[fileName] = QFileInfo("tmp/" + fileName);
    }
    QList<QuaZipFileInfo> destList = testZip.getFileInfoList();
    QCOMPARE(destList.size(), srcInfo.size());
    for (int i = 0; i < destList.size(); i++) {
        QCOMPARE(static_cast<qint64>(destList[i].uncompressedSize),
                srcInfo[destList[i].name].size());
    }
    // test that we didn't mess up the current file
    QCOMPARE(testZip.getCurrentFileName(), firstFile);
    testZip.close();
    // clean up
    removeTestFiles(fileNames);
    curDir.remove(zipName);
}

void TestQuaZip::add_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::addColumn<QStringList>("fileNamesToAdd");
    QTest::newRow("simple") << "qzadd.zip" << (
            QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt")
            << (QStringList() << "testAdd.txt");
}

void TestQuaZip::add()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QFETCH(QStringList, fileNamesToAdd);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Can't create test file");
    }
    if (!createTestArchive(zipName, fileNames)) {
        QFAIL("Can't create test archive");
    }
    if (!createTestFiles(fileNamesToAdd)) {
        QFAIL("Can't create test files to add");
    }
    QuaZip testZip(zipName);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    // according to the bug #3485459 the global is lost, so we test it
    QString globalComment = testZip.getComment();
    testZip.close();
    QVERIFY(testZip.open(QuaZip::mdAdd));
    foreach (QString fileName, fileNamesToAdd) {
        QuaZipFile testFile(&testZip);
        QVERIFY(testFile.open(QIODevice::WriteOnly, 
            QuaZipNewInfo(fileName, "tmp/" + fileName)));
        QFile inFile("tmp/" + fileName);
        QVERIFY(inFile.open(QIODevice::ReadOnly));
        testFile.write(inFile.readAll());
        inFile.close();
        testFile.close();
    }
    testZip.close();
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    QCOMPARE(testZip.getFileNameList(), fileNames + fileNamesToAdd);
    QCOMPARE(testZip.getComment(), globalComment);
    testZip.close();
    removeTestFiles(fileNames);
    removeTestFiles(fileNamesToAdd);
    curDir.remove(zipName);
}

void TestQuaZip::setFileNameCodec_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::addColumn<QByteArray>("encoding");
    QTest::newRow("russian") << QString::fromUtf8("russian.zip") << (
        QStringList() << QString::fromUtf8("тест.txt")) << QByteArray("IBM866");
}

void TestQuaZip::setFileNameCodec()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QFETCH(QByteArray, encoding);
    qSort(fileNames);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Can't create test file");
    }
    if (!createTestArchive(zipName, fileNames,
                           QTextCodec::codecForName(encoding))) {
        QFAIL("Can't create test archive");
    }
    QuaZip testZip(zipName);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    QStringList fileList = testZip.getFileNameList();
    qSort(fileList);
    QVERIFY(fileList[0] != fileNames[0]);
    testZip.close();
    testZip.setFileNameCodec(encoding);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    fileList = testZip.getFileNameList();
    qSort(fileList);
    QCOMPARE(fileList, fileNames);
    testZip.close();
    // clean up
    removeTestFiles(fileNames);
    curDir.remove(zipName);
}

void TestQuaZip::setDataDescriptorWritingEnabled()
{
    QString zipName = "zip10.zip";
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    QuaZip testZip(zipName);
    testZip.setDataDescriptorWritingEnabled(false);
    QVERIFY(testZip.open(QuaZip::mdCreate));
    QuaZipFile testZipFile(&testZip);
    QVERIFY(testZipFile.open(QIODevice::WriteOnly,
                             QuaZipNewInfo("vegetation_info.xml"), NULL, 0, 0));
    testZipFile.write("<vegetation_info version=\"4096\" />\n");
    testZipFile.close();
    testZip.close();
    QCOMPARE(QFileInfo(zipName).size(), static_cast<qint64>(171));
    QFile zipFile(zipName);
    QVERIFY(zipFile.open(QIODevice::ReadOnly));
    QDataStream zipData(&zipFile);
    zipData.setByteOrder(QDataStream::LittleEndian);
    quint32 magic = 0;
    quint16 versionNeeded = 0;
    zipData >> magic;
    zipData >> versionNeeded;
    QCOMPARE(magic, static_cast<quint32>(0x04034b50));
    QCOMPARE(versionNeeded, static_cast<quint16>(10));
    zipFile.close();
    curDir.remove(zipName);
    // now test 2.0
    zipName = "zip20.zip";
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    QuaZip testZip20(zipName);
    QVERIFY(testZip20.open(QuaZip::mdCreate));
    QuaZipFile testZipFile20(&testZip20);
    QVERIFY(testZipFile20.open(QIODevice::WriteOnly,
                             QuaZipNewInfo("vegetation_info.xml"), NULL, 0, 0));
    testZipFile20.write("<vegetation_info version=\"4096\" />\n");
    testZipFile20.close();
    testZip20.close();
    QCOMPARE(QFileInfo(zipName).size(),
            static_cast<qint64>(171 + 16)); // 16 bytes = data descriptor
    QFile zipFile20(zipName);
    QVERIFY(zipFile20.open(QIODevice::ReadOnly));
    QDataStream zipData20(&zipFile20);
    zipData20.setByteOrder(QDataStream::LittleEndian);
    magic = 0;
    versionNeeded = 0;
    zipData20 >> magic;
    zipData20 >> versionNeeded;
    QCOMPARE(magic, static_cast<quint32>(0x04034b50));
    QCOMPARE(versionNeeded, static_cast<quint16>(20));
    zipFile20.close();
    curDir.remove(zipName);
}

void TestQuaZip::testQIODeviceAPI()
{
    QString zipName = "qiodevice_api.zip";
    QStringList fileNames;
    fileNames << "test.txt";
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Can't create test file");
    }
    if (!createTestArchive(zipName, fileNames)) {
        QFAIL("Can't create test archive");
    }
    QBuffer buffer;
    if (!createTestArchive(&buffer, fileNames, NULL)) {
        QFAIL("Can't create test archive");
    }
    QFile diskFile(zipName);
    QVERIFY(diskFile.open(QIODevice::ReadOnly));
    QByteArray bufferArray = buffer.buffer();
    QByteArray fileArray = diskFile.readAll();
    diskFile.close();
    QCOMPARE(bufferArray.size(), fileArray.size());
    QCOMPARE(bufferArray, fileArray);
    curDir.remove(zipName);
}
