#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("CuteMarkEd Project");
    app.setApplicationName("CuteMarkEd");
    app.setApplicationVersion("0.4.1");

    // try to load translation for current locale from resource file
    QTranslator translator;
    translator.load("cutemarked_" + QLocale::system().name(), ":/translations");
    app.installTranslator(&translator);

    // get filename from command line arguments
    QString fileName;
    QStringList cmdLineArgs = app.arguments();
    if (cmdLineArgs.size() > 1) {
        fileName = cmdLineArgs.at(1);
    }

    MainWindow w(fileName);
    w.show();

    return app.exec();
}
