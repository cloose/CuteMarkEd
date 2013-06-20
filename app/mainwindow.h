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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QLabel;
class QNetworkDiskCache;
class ActiveLabel;
class HtmlPreviewGenerator;
class HtmlHighlighter;
class RecentFilesMenu;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(const QString &fileName = QString(), QWidget *parent = 0);
    ~MainWindow();

public slots:
    void webViewScrolled();

protected:
    void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private slots:
    void initializeUI();
    void openRecentFile(const QString &fileName);

    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void fileExportToHtml();
    void fileExportToPdf();
    void filePrint();

    void editUndo();
    void editRedo();
    void editCopyHtml();
    void editFindReplace();
    void editStrong();
    void editEmphasize();
    void editStrikethrough();
    void editInlineCode();
    void editCenterParagraph();
    void editHardLinebreak();
    void editBlockquote();

    void viewChangeSplit();
    void styleDefault();
    void styleGithub();
    void styleSolarizedLight();
    void styleSolarizedDark();
    void styleClearness();
    void styleClearnessDark();
    void viewFullScreenMode();

    void extrasMathSupport(bool checked);
    void extrasCodeHighlighting(bool checked);
    void extrasShowHardLinebreaks(bool checked);

    void helpMarkdownSyntax();
    void helpAbout();

    void styleContextMenu(const QPoint &pos);
    void toggleHtmlView();

    void plainTextChanged();
    void htmlResultReady(const QString &html);
    void tocResultReady(const QString &toc);
    void htmlContentSizeChanged();

    void previewLinkClicked(const QUrl &url);
    void tocLinkClicked(const QUrl &url);

    void splitterMoved(int pos, int index);
    void scrollValueChanged(int value);

    void addJavaScriptObject();
    bool load(const QString &fileName);

private:
    void setupActions();
    void setupStatusBar();
    void setupHtmlPreview();
    void setupHtmlSourceView();
    bool maybeSave();
    void setFileName(const QString &fileName);
    void updateSplitter(bool htmlViewToggled);

private:
    Ui::MainWindow *ui;
    RecentFilesMenu *recentFilesMenu;
    QNetworkDiskCache *diskCache;
    QLabel *styleLabel;
    QLabel *wordCountLabel;
    ActiveLabel *viewLabel;
    HtmlPreviewGenerator* generator;
    HtmlHighlighter *htmlHighlighter;
    QString fileName;
    float splitFactor;
    int scrollBarPos;
};

#endif // MAINWINDOW_H
