#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // try to load translation for current locale from resource file
    QTranslator translator;
    translator.load("cutemarked_" + QLocale::system().name(), ":/translations");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
