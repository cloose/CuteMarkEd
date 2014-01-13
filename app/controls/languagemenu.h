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
#ifndef LANGUAGEMENU_H
#define LANGUAGEMENU_H

#include <QMenu>

class Dictionary;

class LanguageMenu : public QMenu
{
    Q_OBJECT
public:
    explicit LanguageMenu(QWidget *parent = 0);
    
    void loadDictionaries(const QString &currentLanguage);

signals:
    void languageTriggered(const Dictionary &dictionary);

private slots:
    void languageTriggered();

private:
    QAction *createAction(const Dictionary &dictionary);

private:
    QActionGroup *dictionariesGroup;
};

#endif // LANGUAGEMENU_H
