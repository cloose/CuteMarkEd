/*
 * Copyright 2013-2014 Christian Loose <christian.loose@hamburg.de>
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
#include <QCommandLineParser>
#include <QLibraryInfo>
#include <QTranslator>

#ifdef Q_OS_WIN
#include <QDir>
#include <QFileInfo>
#include <QSettings>

// Helper function to register supported file types
// This is needed to enable the application jump list to show the desired recent files
static void associateFileTypes(const QStringList &fileTypes)
{
    QString displayName = QGuiApplication::applicationDisplayName();
    QString filePath = QCoreApplication::applicationFilePath();
    QString fileName = QFileInfo(filePath).fileName();

    QSettings settings("HKEY_CURRENT_USER\\Software\\Classes\\Applications\\" + fileName, QSettings::NativeFormat);
    settings.setValue("FriendlyAppName", displayName);

    settings.beginGroup("SupportedTypes");
    foreach (const QString& fileType, fileTypes)
        settings.setValue(fileType, QString());
    settings.endGroup();

    settings.beginGroup("shell");
    settings.beginGroup("open");
    settings.setValue("FriendlyAppName", displayName);
    settings.beginGroup("Command");
    settings.setValue(".", QChar('"') + QDir::toNativeSeparators(filePath) + QString("\" \"%1\""));
}
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("CuteMarkEd Project");
    app.setApplicationName("CuteMarkEd");
    app.setApplicationDisplayName("CuteMarkEd");
    app.setApplicationVersion("0.11.3");

#ifdef Q_OS_WIN
    QStringList fileTypes;
    fileTypes << ".markdown" << ".md" << ".mdown";
    associateFileTypes(fileTypes);
#endif

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

    // setup command line parser
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", QApplication::translate("main", "The file to open."));
    parser.process(app);

    // get filename from command line arguments
    QString fileName;
    const QStringList cmdLineArgs = parser.positionalArguments();
    if (!cmdLineArgs.isEmpty()) {
        fileName = cmdLineArgs.at(0);
    }

    MainWindow w(fileName);
    w.show();

    return app.exec();
}
