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
#include "spellchecker.h"
using hunspell::SpellChecker;

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>
#include <QTextCodec>

#include <hunspell/hunspell.hxx>

#include <spellchecker/dictionary.h>

SpellChecker::SpellChecker() :
    hunspellChecker(0),
    textCodec(0)
{
}

SpellChecker::~SpellChecker()
{
    delete hunspellChecker;
}

bool SpellChecker::isCorrect(const QString &word)
{
    if (!textCodec || !hunspellChecker) {
        return true;
    }

    QByteArray ba = textCodec->fromUnicode(word);
    return hunspellChecker->spell(ba) != 0;
}

QStringList SpellChecker::suggestions(const QString &word)
{
    QStringList suggestions;

    if (!textCodec || !hunspellChecker) {
        return suggestions;
    }

    char **suggestedWords;
    QByteArray ba = textCodec->fromUnicode(word);
    int count = hunspellChecker->suggest(&suggestedWords, ba);

    for (int i = 0; i < count; ++i) {
        suggestions << textCodec->toUnicode(suggestedWords[i]);
    }

    hunspellChecker->free_list(&suggestedWords, count);

    return suggestions;
}

void SpellChecker::addToUserWordlist(const QString &word)
{
    hunspellChecker->add(textCodec->fromUnicode(word).constData());
    if(!userWordlist.isEmpty()) {
        QFile userWordlistFile(userWordlist);
        if(!userWordlistFile.open(QIODevice::Append))
            return;

        QTextStream stream(&userWordlistFile);
        stream << word << "\n";
        userWordlistFile.close();
    }
}

void SpellChecker::loadDictionary(const QString &dictFilePath)
{
    delete hunspellChecker;

    qDebug() << "Load dictionary from path" << dictFilePath;

    QString affixFilePath(dictFilePath);
    affixFilePath.replace(".dic", ".aff");

    hunspellChecker = new Hunspell(affixFilePath.toLocal8Bit(), dictFilePath.toLocal8Bit());

    textCodec = QTextCodec::codecForName(hunspellChecker->get_dic_encoding());
    if (!textCodec) {
        textCodec = QTextCodec::codecForName("UTF-8");
    }

    // also load user word list
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    loadUserWordlist(path + "/user.dic");
}

void SpellChecker::loadUserWordlist(const QString &userWordlistPath)
{
    userWordlist = userWordlistPath;

    QFile userWordlistFile(userWordlistPath);
    if (!userWordlistFile.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&userWordlistFile);
    for (QString word = stream.readLine(); !word.isEmpty(); word = stream.readLine()) {
        hunspellChecker->add(textCodec->fromUnicode(word).constData());
    }
}

QMap<QString, Dictionary> SpellChecker::availableDictionaries()
{
    QMap<QString, Dictionary> dictionaries;

    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
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
