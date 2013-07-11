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
#include "imainwindow.h"

namespace Ui {
class MainWindow;
}

class QActionGroup;
class QLabel;
class QNetworkDiskCache;
class ActiveLabel;
class HtmlHighlighter;
class MainWindowPresenter;
class Options;


class MainWindow : public QMainWindow, IMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(const QString &fileName = QString(), QWidget *parent = 0);
    ~MainWindow();

    // IMainWindow interface
    QString markdownText() const Q_DECL_OVERRIDE;
    void setMarkdownText(const QString &text) Q_DECL_OVERRIDE;
    void setMarkdownTextModified(bool modified) Q_DECL_OVERRIDE;
    QTextDocument *markdownDocument() const Q_DECL_OVERRIDE;
    void setHtml(const QString &html) Q_DECL_OVERRIDE;
    void setTableOfContents(const QString &toc) Q_DECL_OVERRIDE;
    void updateWindowTitle(const QString &fileName) Q_DECL_OVERRIDE;
    bool maybeSave() Q_DECL_OVERRIDE;

public slots:
    void webViewScrolled();

protected:
    void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private slots:
    void initializeApp();

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
    void styleCustomStyle();
    void viewFullScreenMode();

    void extrasMathSupport(bool checked);
    void extrasCodeHighlighting(bool checked);
    void extrasShowHardLinebreaks(bool checked);
    void extrasOptions();

    void helpMarkdownSyntax();
    void helpAbout();

    void styleContextMenu(const QPoint &pos);
    void toggleHtmlView();

    void plainTextChanged();
    void htmlContentSizeChanged();

    void previewLinkClicked(const QUrl &url);
    void tocLinkClicked(const QUrl &url);

    void splitterMoved(int pos, int index);
    void scrollValueChanged(int value);

    void addJavaScriptObject();
    void proxyConfigurationChanged();

private:
    void setupUi();
    void setupActions();
    void setupStatusBar();
    void setupMarkdownEditor();
    void setupHtmlPreview();
    void setupHtmlSourceView();
    void updateSplitter(bool htmlViewToggled);
    void loadCustomStyles();
    void readSettings();
    void writeSettings();

private:
    Ui::MainWindow *ui;
    MainWindowPresenter *presenter;
    Options *options;
    QNetworkDiskCache *diskCache;
    QActionGroup *stylesGroup;
    QLabel *styleLabel;
    QLabel *wordCountLabel;
    ActiveLabel *viewLabel;
    HtmlHighlighter *htmlHighlighter;
    float splitFactor;
    int scrollBarPos;
};

#endif // MAINWINDOW_H
