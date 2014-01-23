#ifndef QUAZIP_TEST_QUAZIP_H
#define QUAZIP_TEST_QUAZIP_H

#include <QObject>

class TestQuaZip: public QObject {
    Q_OBJECT
private slots:
    void getFileList_data();
    void getFileList();
    void add_data();
    void add();
    void setFileNameCodec_data();
    void setFileNameCodec();
    void setDataDescriptorWritingEnabled();
    void testQIODeviceAPI();
};

#endif // QUAZIP_TEST_QUAZIP_H
