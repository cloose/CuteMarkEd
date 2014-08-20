/*
 * Copyright 2014 Christian Loose <christian.loose@hamburg.de>
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
#include "spellchecker.h"
using hunspell::SpellChecker;

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QDirIterator>

#include <spellchecker/dictionary.h>
#include <datalocation.h>

QMap<QString, Dictionary> SpellChecker::availableDictionaries()
{
    QMap<QString, Dictionary> dictionaries;

    QStringList paths = DataLocation::standardLocations();
    paths << qApp->applicationDirPath();

    foreach (const QString &path, paths) {
        QDir dictPath(path + QDir::separator() + "dictionaries");
        dictPath.setFilter(QDir::Files);
        dictPath.setNameFilters(QStringList() << "*.dic");
        if (dictPath.exists()) {
            // loop over all dictionaries in directory
            QDirIterator it(dictPath);
            while (it.hasNext()) {
                it.next();

                QString language = it.fileName().remove(".dic");
                language.truncate(5); // just language and country code

                Dictionary dict(it.fileName(), it.filePath());
                dictionaries.insert(language, dict);
            }
        }
    }

    return dictionaries;
}
