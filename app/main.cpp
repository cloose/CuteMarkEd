#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    a.setStyleSheet("QStatusBar::item { border: 0px solid black }; ");

    return a.exec();
}
