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
#ifndef SNIPPETCOMPLETER_H
#define SNIPPETCOMPLETER_H

#include <QObject>

class QCompleter;
class QPlainTextEdit;
class SnippetRepository;
struct Snippet;


class SnippetCompleter : public QObject
{
    Q_OBJECT
public:
    explicit SnippetCompleter(QPlainTextEdit *textEdit);

    void performCompletion();

    bool isPopupVisible() const;
    void hidePopup();
    void setPopupOffset(int leftOffset);

    void setSnippetRepository(SnippetRepository *repository);

public slots:
    void updateModel();

private slots:
    void insertSnippet(const QString &trigger);

private:
    QString textUnderCursor() const;
    void replaceClipboardVariable(QString &snippetContent);

private:
    QPlainTextEdit *editor;
    SnippetRepository *snippetRepository;
    QCompleter *completer;
    int popupOffset;
};

#endif // SNIPPETCOMPLETER_H
