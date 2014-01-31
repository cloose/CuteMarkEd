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
#include "mainwindow.h"

#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("CuteMarkEd Project");
    app.setApplicationName("CuteMarkEd");
    app.setApplicationDisplayName("CuteMarkEd");
    app.setApplicationVersion("0.9.1");

    // load translation for Qt
    QTranslator qtTranslator;
    if (!qtTranslator.load("qt_" + QLocale::system().name(),
                           QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
        qtTranslator.load("qt_" + QLocale::system().name(), "translations");
    }
    app.installTranslator(&qtTranslator);

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
