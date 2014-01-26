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
#include "languagemenu.h"

#include <spellchecker/dictionary.h>
#include "hunspell/spellchecker.h"

LanguageMenu::LanguageMenu(QWidget *parent) :
    QMenu(tr("Languages"), parent),
    dictionariesGroup(new QActionGroup(this))
{
}

void LanguageMenu::loadDictionaries(const QString &currentLanguage)
{
    QMap<QString, Dictionary> dictionaries = hunspell::SpellChecker::availableDictionaries();

    QMapIterator<QString, Dictionary> it(dictionaries);
    while (it.hasNext()) {
        it.next();

        Dictionary dictionary = it.value();

        // create an action for the dictionary
        QAction *action = createAction(dictionary);

        if (dictionary.language() == currentLanguage) {
            action->setChecked(true);
            action->trigger();
        }
    }
}

void LanguageMenu::languageTriggered()
{
    QAction *action = qobject_cast<QAction*>(sender());
    emit languageTriggered(action->data().value<Dictionary>());
}

QAction *LanguageMenu::createAction(const Dictionary &dictionary)
{
    QAction *action = this->addAction(QString("%1 / %2").arg(dictionary.languageName()).arg(dictionary.countryName()), this, SLOT(languageTriggered()));
    action->setCheckable(true);
    action->setActionGroup(dictionariesGroup);

    QVariant data;
    data.setValue(dictionary);
    action->setData(data);

    return action;
}
