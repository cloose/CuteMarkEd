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
#ifndef FINDREPLACEWIDGET_H
#define FINDREPLACEWIDGET_H

#include <QWidget>
#include <QTextDocument>

namespace Ui {
class FindReplaceWidget;
}
class QPlainTextEdit;

class FindReplaceWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FindReplaceWidget(QWidget *parent = 0);
    ~FindReplaceWidget();
    
    void setTextEdit(QPlainTextEdit *editor);

protected:
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

private slots:
    void findPreviousClicked();
    void findNextClicked();
    void replaceClicked();
    void replaceAllClicked();

    void caseSensitiveToggled(bool enabled);
    void wholeWordsOnlyToggled(bool enabled);
    void useRegularExpressionsToggled(bool enabled);

private:
    void setupFindOptionsMenu();
    bool find(const QString &searchString, QTextDocument::FindFlags findOptions = 0) const;
    bool findUsingRegExp(const QString &pattern, QTextDocument::FindFlags findOptions = 0) const;

    Ui::FindReplaceWidget *ui;
    QPlainTextEdit *textEditor;

    bool findCaseSensitively;
    bool findWholeWordsOnly;
    bool findUseRegExp;
};

#endif // FINDREPLACEWIDGET_H
