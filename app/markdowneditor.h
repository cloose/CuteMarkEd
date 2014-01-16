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
#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <qplaintextedit.h>

class Dictionary;
namespace hunspell {
class SpellChecker;
}
class MarkdownHighlighter;
class SnippetCompleter;


class MarkdownEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MarkdownEditor(QWidget *parent = 0);
    ~MarkdownEditor();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    void resetHighlighting();
    void loadStyleFromStylesheet(const QString &fileName);

    int countWords() const;

    void setShowSpecialCharacters(bool enabled);
    void setSpellingCheckEnabled(bool enabled);
    void setSpellingDictionary(const Dictionary &dictionary);

    void setSnippetCompleter(SnippetCompleter *completer);
    void gotoLine(int line);

signals:
    void loadDroppedFile(const QString &fileName);

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
    bool canInsertFromMimeData(const QMimeData *source) const Q_DECL_OVERRIDE;
    void insertFromMimeData(const QMimeData *source) Q_DECL_OVERRIDE;

public slots:
    void tabWidthChanged(int tabWidth);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);
    void editorFontChanged(const QFont &font);
    void showContextMenu(const QPoint &pos);
    void replaceWithSuggestion();
    void performCompletion();
    void insertSnippet(const QString &completionPrefix, const QString &completion, int newCursorPos);
    void addWordToUserWordlist();

private:
    void drawLineEndMarker(QPaintEvent *e);
    QString textUnderCursor() const;

private:
    QWidget *lineNumberArea;
    MarkdownHighlighter *highlighter;
    hunspell::SpellChecker *spellChecker;
    SnippetCompleter *completer;
    bool showHardLinebreaks;
};

#endif // MARKDOWNEDITOR_H
