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
#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include <QObject>

class IMainWindow;
class HtmlPreviewGenerator;
class MarkdownManipulator;
class RecentFilesMenu;


class MainWindowPresenter : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowPresenter(IMainWindow *view, QObject *parent = 0);
    ~MainWindowPresenter();
    
    void onViewReady();

    QUrl previewBaseUrl() const;

    void setMarkdownManipulator(MarkdownManipulator *manipulator);
    void setRecentFilesMenu(RecentFilesMenu *menu);

    void setMathSupportEnabled(bool enabled);
    void setCodeHighlightingEnabled(bool enabled);
    void setCodeHighlightingStyle(const QString &style);

    QString fileName() const;
    void setFileName(const QString &fileName);

    void readSettings();
    void writeSettings();

public slots:
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

    void editStrong();
    void editEmphasize();
    void editStrikethrough();
    void editInlineCode();
    void editCenterParagraph();
    void editHardLinebreak();
    void editBlockquote();

private slots:
    void markdownTextChanged();

    void htmlResultReady(const QString &html);
    void tocResultReady(const QString &toc);

    void openRecentFile(const QString &fileName);

private:
    void addToRecentFiles(const QString &fileName);

private:
    IMainWindow *view;
    HtmlPreviewGenerator *generator;
    MarkdownManipulator *manipulator;
    RecentFilesMenu *recentFilesMenu;
    QString m_fileName;
};

#endif // MAINWINDOWPRESENTER_H
