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
class SnippetCollection;
struct Snippet;


class SnippetCompleter : public QObject
{
    Q_OBJECT
public:
    explicit SnippetCompleter(QWidget *parentWidget);

    void performCompletion(const QString &textUnderCursor, const QRect &popupRect);

    bool isPopupVisible() const;
    void hidePopup();
    void setPopupOffset(int leftOffset);

    void setSnippetCollection(SnippetCollection *collection);

signals:
    void snippetSelected(const QString &trigger, const QString &snippetContent, int newCursorPos);

public slots:
    void updateModel();

private slots:
    void insertSnippet(const QString &trigger);

private:
    void replaceClipboardVariable(QString &snippetContent);
    int longestTriggerLength() const;

private:
    SnippetCollection *snippetCollection;
    QCompleter *completer;
    int popupOffset;
};

#endif // SNIPPETCOMPLETER_H
