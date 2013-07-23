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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QDirIterator>
#include <QFileDialog>
#include <QIcon>
#include <QLabel>
#include <QMessageBox>
#include <QNetworkDiskCache>
#include <QNetworkProxy>
#include <QPrintDialog>
#include <QPrinter>
#include <QScrollBar>
#include <QSettings>
#include <QStandardPaths>
#include <QTextDocumentWriter>
#include <QTimer>
#include <QWebFrame>
#include <QWebPage>
#include <QWebInspector>

#include "controls/activelabel.h"
#include "controls/findreplacewidget.h"
#include "controls/recentfilesmenu.h"
#include "hunspell/dictionary.h"
#include "hunspell/spellchecker.h"
#include "htmlpreviewgenerator.h"
#include "htmlhighlighter.h"
#include "markdownmanipulator.h"
#include "exporthtmldialog.h"
#include "exportpdfdialog.h"
#include "options.h"
#include "optionsdialog.h"

MainWindow::MainWindow(const QString &fileName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    options(new Options(this)),
    styleLabel(0),
    wordCountLabel(0),
    viewLabel(0),
    generator(new HtmlPreviewGenerator(options, this)),
    splitFactor(0.5),
    scrollBarPos(0)
{
    ui->setupUi(this);
    setupUi();

    setFileName(fileName);

    QTimer::singleShot(0, this, SLOT(initializeApp()));
}

MainWindow::~MainWindow()
{
    // stop background HTML preview generator
    generator->enqueue(QString());
    generator->wait();
    delete generator;

    delete ui;
}

void MainWindow::webViewScrolled()
{
    double factor = (double)ui->plainTextEdit->verticalScrollBar()->maximum() /
                   ui->webView->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    int value = ui->webView->page()->mainFrame()->scrollBarValue(Qt::Vertical);

    ui->plainTextEdit->verticalScrollBar()->setValue(qRound(value * factor));
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    // check if file needs saving
    if (maybeSave()) {
        writeSettings();
        e->accept();
    } else {
        e->ignore();
    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    updateSplitter(false);
}

void MainWindow::initializeApp()
{
    // inform us when a link in the table of contents or preview view is clicked
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    ui->tocWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    // set default style
    styleDefault();

    // init extension flags
    ui->actionAutolink->setChecked(options->isAutolinkEnabled());
    ui->actionStrikethroughOption->setChecked(options->isStrikethroughEnabled());
    ui->actionAlphabeticLists->setChecked(options->isAlphabeticListsEnabled());
    ui->actionDefinitionLists->setChecked(options->isDefinitionListsEnabled());
    ui->actionSmartyPants->setChecked(options->isSmartyPantsEnabled());

    // init option flags
    ui->actionCheckSpelling->setChecked(options->isSpellingCheckEnabled());
    ui->plainTextEdit->setSpellingCheckEnabled(options->isSpellingCheckEnabled());

    // set url to markdown syntax help
    ui->webView_2->setUrl(tr("qrc:/syntax.html"));

    // load remote javascript and use system proxy configuration
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);

    // setup disk cache for network access
    diskCache = new QNetworkDiskCache(this);
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(cacheDir);

//    ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
//    QWebInspector *inspector = new QWebInspector();
//    inspector->setPage(ui->webView->page());

    loadCustomStyles();
    loadDictionaries();

    // load file passed to application on start
    if (!fileName.isEmpty()) {
        load(fileName);
    }
}

void MainWindow::openRecentFile(const QString &fileName)
{
    if (maybeSave()) {
        load(fileName);
    }
}

void MainWindow::fileNew()
{
    if (maybeSave()) {
        wordCountLabel->setText("");
        wordCountLabel->setToolTip("");
        ui->plainTextEdit->clear();
        ui->plainTextEdit->resetHighlighting();
        ui->webView->setHtml(QString());
        ui->htmlSourceTextEdit->clear();
        setFileName(QString());
    }
}

void MainWindow::fileOpen()
{
    if (maybeSave()) {
        QString name = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                                    QString(), tr("Markdown Files (*.markdown *.md);;All Files (*)"));
        if (!name.isEmpty()) {
            load(name);
        }
    }
}

bool MainWindow::fileSave()
{
    if (fileName.isEmpty()) {
        return fileSaveAs();
    }

    QTextDocumentWriter writer(fileName, "plaintext");
    bool success = writer.write(ui->plainTextEdit->document());
    if (success) {
        // set status to unmodified
        ui->plainTextEdit->document()->setModified(false);
        setWindowModified(false);

        // add to recent file list
        recentFilesMenu->addFile(QDir::toNativeSeparators(fileName));
    }

    return success;
}

bool MainWindow::fileSaveAs()
{
    QString name = QFileDialog::getSaveFileName(this, tr("Save as..."), QString(),
                                              tr("Markdown Files (*.markdown *.md);;All Files (*)"));
    if (name.isEmpty()) {
        return false;
    }

    setFileName(name);
    return fileSave();
}

void MainWindow::fileExportToHtml()
{
    ExportHtmlDialog dialog(fileName);
    if (dialog.exec() == QDialog::Accepted) {

        if (dialog.includeCSS()) {
            // get url of current css stylesheet
            QUrl cssUrl = ui->webView->page()->settings()->userStyleSheetUrl();

            // get resource or file name from url
            QString cssFileName;
            if (cssUrl.scheme() == "qrc") {
                cssFileName = cssUrl.toString().remove(0, 3);
            } else {
                cssFileName = cssUrl.toLocalFile();
            }

            // read currently used css stylesheet file
            QFile f(cssFileName);
            if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QString cssStyle = f.readAll();

                // embed the css into the HTML source document after the <head> element.
                if (ui->htmlSourceTextEdit->find("<head>")) {
                    QTextCursor cursor = ui->htmlSourceTextEdit->textCursor();
                    cursor.beginEditBlock();
                    cursor.setPosition(cursor.selectionEnd());
                    cursor.insertText(QString("\n<style>%1</style>").arg(cssStyle));
                    cursor.endEditBlock();
                }
            }
        }

        // write HTML source to disk
        QTextDocumentWriter writer(dialog.fileName(), "plaintext");
        writer.write(ui->htmlSourceTextEdit->document());

        // undo the changes to the HTML source
        if (dialog.includeCSS()) {
            ui->htmlSourceTextEdit->undo();
        }
    }
}

void MainWindow::fileExportToPdf()
{
    ExportPdfDialog dialog(fileName);
    if (dialog.exec() == QDialog::Accepted) {
        ui->webView->print(dialog.printer());
    }
}

void MainWindow::filePrint()
{
    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    dlg->setWindowTitle(tr("Print Document"));

    if (ui->webView->hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);

    if (dlg->exec() == QDialog::Accepted)
        ui->webView->print(&printer);

    delete dlg;
}

void MainWindow::editUndo()
{
    if (ui->plainTextEdit->document()->isUndoAvailable()) {
        ui->plainTextEdit->document()->undo();
    }
}

void MainWindow::editRedo()
{
    if (ui->plainTextEdit->document()->isRedoAvailable()) {
        ui->plainTextEdit->document()->redo();
    }
}

void MainWindow::editCopyHtml()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(ui->htmlSourceTextEdit->toPlainText());
}

void MainWindow::editFindReplace()
{
    ui->findReplaceWidget->setTextEdit(ui->plainTextEdit);
    ui->findReplaceWidget->show();
    ui->findReplaceWidget->setFocus();
}

void MainWindow::editStrong()
{
    MarkdownManipulator manipulator(ui->plainTextEdit);
    manipulator.wrapSelectedText("**");
}

void MainWindow::editEmphasize()
{
    MarkdownManipulator manipulator(ui->plainTextEdit);
    manipulator.wrapSelectedText("*");
}

void MainWindow::editStrikethrough()
{
    MarkdownManipulator manipulator(ui->plainTextEdit);
    manipulator.wrapSelectedText("~~");
}

void MainWindow::editInlineCode()
{
    MarkdownManipulator manipulator(ui->plainTextEdit);
    manipulator.wrapSelectedText("`");
}

void MainWindow::editCenterParagraph()
{
    MarkdownManipulator manipulator(ui->plainTextEdit);
    manipulator.wrapCurrentParagraph("->", "<-");
}

void MainWindow::editHardLinebreak()
{
    MarkdownManipulator manipulator(ui->plainTextEdit);
    manipulator.appendToLine("  \n");
}

void MainWindow::editBlockquote()
{
    MarkdownManipulator manipulator(ui->plainTextEdit);
    manipulator.prependToLine('>');
}

void MainWindow::viewChangeSplit()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action->objectName() == ui->actionSplit_1_1->objectName()) {
        splitFactor = 0.5;
    } else if (action->objectName() == ui->actionSplit_2_1->objectName()) {
        splitFactor = 0.666;
    } else if (action->objectName() == ui->actionSplit_1_2->objectName()) {
        splitFactor = 0.333;
    } else if (action->objectName() == ui->actionSplit_3_1->objectName()) {
        splitFactor = 0.75;
    } else if (action->objectName() == ui->actionSplit_1_3->objectName()) {
        splitFactor = 0.25;
    }

    updateSplitter(true);
}

void MainWindow::styleDefault()
{
    ui->plainTextEdit->loadStyleFromStylesheet(":/theme/default.txt");
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/markdown.css"));

    generator->setCodeHighlightingStyle("default");
    plainTextChanged();

    styleLabel->setText(ui->actionDefault->text());
}

void MainWindow::styleGithub()
{
    ui->plainTextEdit->loadStyleFromStylesheet(":/theme/default.txt");
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/github.css"));

    generator->setCodeHighlightingStyle("github");
    plainTextChanged();

    styleLabel->setText(ui->actionGithub->text());
}

void MainWindow::styleSolarizedLight()
{
    ui->plainTextEdit->loadStyleFromStylesheet(":/theme/solarized-light+.txt");
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/solarized-light.css"));

    generator->setCodeHighlightingStyle("solarized_light");
    plainTextChanged();

    styleLabel->setText(ui->actionSolarizedLight->text());
}

void MainWindow::styleSolarizedDark()
{
    ui->plainTextEdit->loadStyleFromStylesheet(":/theme/solarized-dark+.txt");
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/solarized-dark.css"));

    generator->setCodeHighlightingStyle("solarized_dark");
    plainTextChanged();

    styleLabel->setText(ui->actionSolarizedDark->text());
}

void MainWindow::styleClearness()
{
    ui->plainTextEdit->loadStyleFromStylesheet(":/theme/default.txt");
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/clearness.css"));

    generator->setCodeHighlightingStyle("default");
    plainTextChanged();

    styleLabel->setText(ui->actionClearness->text());
}

void MainWindow::styleClearnessDark()
{
    ui->plainTextEdit->loadStyleFromStylesheet(":/theme/clearness-dark+.txt");
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/css/clearness-dark.css"));

    generator->setCodeHighlightingStyle("default");
    plainTextChanged();

    styleLabel->setText(ui->actionClearnessDark->text());
}

void MainWindow::styleCustomStyle()
{
    QAction *action = qobject_cast<QAction*>(sender());

    ui->plainTextEdit->loadStyleFromStylesheet(":/theme/default.txt");
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(action->data().toString()));

    generator->setCodeHighlightingStyle("default");
    plainTextChanged();

    styleLabel->setText(action->text());
}

void MainWindow::viewFullScreenMode()
{
    if (ui->actionFullScreenMode->isChecked()) {
        showFullScreen();
    } else {
        showNormal();
    }
}

void MainWindow::extrasMathSupport(bool checked)
{
    generator->setMathSupportEnabled(checked);
    plainTextChanged();
}

void MainWindow::extrasCodeHighlighting(bool checked)
{
    generator->setCodeHighlightingEnabled(checked);
    plainTextChanged();
}

void MainWindow::extrasShowHardLinebreaks(bool checked)
{
    ui->plainTextEdit->setShowHardLinebreaks(checked);
}

void MainWindow::extensionsAutolink(bool checked)
{
    options->setAutolinkEnabled(checked);
    plainTextChanged();
}

void MainWindow::extensionsStrikethrough(bool checked)
{
    options->setStrikethroughEnabled(checked);
    plainTextChanged();
}

void MainWindow::extensionsAlphabeticLists(bool checked)
{
    options->setAlphabeticListsEnabled(checked);
    plainTextChanged();
}

void MainWindow::extensionsDefinitionLists(bool checked)
{
    options->setDefinitionListsEnabled(checked);
    plainTextChanged();
}

void MainWindow::extensionsSmartyPants(bool checked)
{
    options->setSmartyPantsEnabled(checked);
    plainTextChanged();
}

void MainWindow::extrasCheckSpelling(bool checked)
{
    ui->plainTextEdit->setSpellingCheckEnabled(checked);
    options->setSpellingCheckEnabled(checked);
}

void MainWindow::extrasLanguage()
{
    QAction *action = qobject_cast<QAction*>(sender());

    hunspell::Dictionary dictionary = action->data().value<hunspell::Dictionary>();
    options->setDictionaryLanguage(dictionary.language());

    ui->plainTextEdit->setSpellingDictionary(dictionary);
}

void MainWindow::extrasOptions()
{
    OptionsDialog dialog(options, this);
    if (dialog.exec() == QDialog::Accepted) {
        options->writeSettings();
    }
}

void MainWindow::helpMarkdownSyntax()
{
    ui->dockWidget_2->show();
}

void MainWindow::helpAbout()
{
    QMessageBox::about(this, tr("About CuteMarkEd"),
                       tr("<p><b>CuteMarkEd %1</b><br>Qt-based, free and open source markdown editor with live HTML preview<br>Copyright 2013 Christian Loose</p><p><a href=\"http://cloose.github.io/CuteMarkEd\">http://cloose.github.io/CuteMarkEd</a></p>")
                       .arg(qApp->applicationVersion()));
}

void MainWindow::styleContextMenu(const QPoint &pos)
{
    QMenu *menu = new QMenu();
    menu->addActions(stylesGroup->actions());

    menu->exec(styleLabel->mapToGlobal(pos));
}

void MainWindow::toggleHtmlView()
{
    if (viewLabel->text() == tr("HTML preview")) {
        ui->webView->hide();
        ui->htmlSourceTextEdit->show();
        ui->actionHtmlPreview->setText(tr("HTML source"));
        viewLabel->setText(tr("HTML source"));
    } else {
        ui->webView->show();
        ui->htmlSourceTextEdit->hide();
        ui->actionHtmlPreview->setText(tr("HTML preview"));
        viewLabel->setText(tr("HTML preview"));
    }

    updateSplitter(true);
}

void MainWindow::plainTextChanged()
{
    QString code = ui->plainTextEdit->toPlainText();

    // update statistics
    if (wordCountLabel) {
        int words = ui->plainTextEdit->countWords();
        int lines = ui->plainTextEdit->document()->lineCount();
        int chars = ui->plainTextEdit->document()->characterCount();
        wordCountLabel->setText(tr("%1 words").arg(words));
        wordCountLabel->setToolTip(tr("Lines: %1  Words: %2  Characters: %3").arg(lines).arg(words).arg(chars));
    }

    // generate HTML from markdown
    generator->enqueue(code);

    // show modification indicator in window title
    setWindowModified(ui->plainTextEdit->document()->isModified());
}

void MainWindow::htmlResultReady(const QString &html)
{
    ui->webView->page()->networkAccessManager()->setCache(diskCache);

    // remember scrollbar position
    scrollBarPos = ui->plainTextEdit->verticalScrollBar()->value();

    QUrl baseUrl;
    if (fileName.isEmpty()) {
        baseUrl = QUrl::fromLocalFile(qApp->applicationDirPath());
    } else {
        baseUrl = QUrl::fromLocalFile(QFileInfo(fileName).absolutePath() + "/");
    }
    ui->webView->setHtml(html, baseUrl);

    ui->htmlSourceTextEdit->setPlainText(html);
}

void MainWindow::tocResultReady(const QString &toc)
{
    QString styledToc = QString("<html><head>\n<style type=\"text/css\">ul { list-style-type: none; padding: 0; margin-left: 1em; } a { text-decoration: none; }</style>\n</head><body>%1</body></html>").arg(toc);
    ui->tocWebView->setHtml(styledToc);
}

void MainWindow::htmlContentSizeChanged()
{
    if (scrollBarPos > 0) {
        // restore previous scrollbar position
        scrollValueChanged(scrollBarPos);
    }
}

void MainWindow::previewLinkClicked(const QUrl &url)
{
    // only open link if its not a local directory.
    // this can happen because when the href is empty, url is the base url (see htmlResultReady)
    if (!url.isLocalFile() || !QFileInfo(url.toLocalFile()).isDir()) {
        ui->webView->load(url);
    }
}

void MainWindow::tocLinkClicked(const QUrl &url)
{
    QString anchor = url.toString().remove("#");
    ui->webView->page()->mainFrame()->scrollToAnchor(anchor);
}

void MainWindow::splitterMoved(int pos, int index)
{
    Q_UNUSED(index)
    splitFactor = (float)pos / ui->splitter->size().width();
}

void MainWindow::scrollValueChanged(int value)
{
    double factor = (double)ui->webView->page()->mainFrame()->scrollBarMaximum(Qt::Vertical) /
                   ui->plainTextEdit->verticalScrollBar()->maximum();

    ui->webView->page()->mainFrame()->setScrollBarValue(Qt::Vertical, qRound(value * factor));
}

void MainWindow::addJavaScriptObject()
{
    // add mainwindow object to javascript engine, so when
    // the scrollbar of the webview changes the method webViewScrolled() can be called
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("mainwin", this);
}

bool MainWindow::load(const QString &fileName)
{
    if (!QFile::exists(fileName)) {
        return false;
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    QByteArray content = file.readAll();
    QString text = QString::fromUtf8(content);

    ui->plainTextEdit->resetHighlighting();
    ui->plainTextEdit->setPlainText(text);

    setFileName(fileName);
    recentFilesMenu->addFile(QDir::toNativeSeparators(fileName));
    return true;
}

void MainWindow::proxyConfigurationChanged()
{
    if (options->proxyMode() == Options::SystemProxy) {
        qDebug() << "Use system proxy configuration";
        QNetworkProxyFactory::setUseSystemConfiguration(true);
    } else if (options->proxyMode() == Options::ManualProxy) {
        qDebug() << "Use proxy" << options->proxyHost();
        QNetworkProxyFactory::setUseSystemConfiguration(false);

        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(options->proxyHost());
        proxy.setPort(options->proxyPort());
        proxy.setUser(options->proxyUser());
        proxy.setPassword(options->proxyPassword());
        QNetworkProxy::setApplicationProxy(proxy);
    } else {
        qDebug() << "Don't use a proxy";
        QNetworkProxyFactory::setUseSystemConfiguration(false);

        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::NoProxy);
        QNetworkProxy::setApplicationProxy(proxy);
    }
}

void MainWindow::setupUi()
{
    setupActions();
    setupStatusBar();
    setupMarkdownEditor();
    setupHtmlPreview();
    setupHtmlSourceView();

    // hide find/replace widget on startup
    ui->findReplaceWidget->hide();

    // close table of contents dockwidget
    ui->dockWidget->close();

    // hide markdown syntax help dockwidget
    ui->dockWidget_2->hide();
    ui->dockWidget_2->setFloating(true);
    ui->dockWidget_2->resize(550, 400);

    // show HTML preview on right panel
    toggleHtmlView();

    connect(options, SIGNAL(proxyConfigurationChanged()),
            this, SLOT(proxyConfigurationChanged()));

    readSettings();
}

void MainWindow::setupActions()
{
    // file menu
    ui->actionNew->setShortcut(QKeySequence::New);
    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSave->setIcon(QIcon("icon-save.fontawesome"));
    ui->actionSaveAs->setShortcut(QKeySequence::SaveAs);
    ui->action_Print->setShortcut(QKeySequence::Print);
    ui->action_Print->setIcon(QIcon("icon-print.fontawesome"));
    ui->actionExit->setShortcut(QKeySequence::Quit);

    recentFilesMenu = new RecentFilesMenu(ui->menuFile);
    ui->menuFile->insertMenu(ui->actionSave, recentFilesMenu);

    connect(recentFilesMenu, SIGNAL(recentFileTriggered(QString)),
            this, SLOT(openRecentFile(QString)));

    // edit menu
    ui->actionUndo->setShortcut(QKeySequence::Undo);
    ui->actionUndo->setIcon(QIcon("icon-undo.fontawesome"));
    ui->actionRedo->setShortcut(QKeySequence::Redo);
    ui->actionRedo->setIcon(QIcon("icon-repeat.fontawesome"));

    ui->actionCut->setShortcut(QKeySequence::Cut);
    ui->actionCut->setIcon(QIcon("icon-cut.fontawesome"));
    ui->actionCopy->setShortcut(QKeySequence::Copy);
    ui->actionCopy->setIcon(QIcon("icon-copy.fontawesome"));
    ui->actionPaste->setShortcut(QKeySequence::Paste);
    ui->actionPaste->setIcon(QIcon("icon-paste.fontawesome"));
    ui->actionStrong->setShortcut(QKeySequence::Bold);
    ui->actionStrong->setIcon(QIcon("icon-bold.fontawesome"));
    ui->actionEmphasize->setShortcut(QKeySequence::Italic);
    ui->actionEmphasize->setIcon(QIcon("icon-italic.fontawesome"));
    ui->actionStrikethrough->setIcon(QIcon("icon-strikethrough.fontawesome"));
    ui->actionCenterParagraph->setIcon(QIcon("icon-align-center.fontawesome"));
    ui->actionHardLinebreak->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return));
    ui->actionBlockquote->setIcon(QIcon("icon-quote-left.fontawesome"));

    ui->actionFindReplace->setShortcut(QKeySequence::Find);
    ui->actionFindReplace->setIcon(QIcon("icon-search.fontawesome"));
    ui->actionFindNext->setShortcut(QKeySequence::FindNext);
    ui->actionFindPrevious->setShortcut(QKeySequence::FindPrevious);

    connect(ui->actionFindNext, SIGNAL(triggered()),
            ui->findReplaceWidget, SLOT(findNextClicked()));

    connect(ui->actionFindPrevious, SIGNAL(triggered()),
            ui->findReplaceWidget, SLOT(findPreviousClicked()));

    // view menu
    ui->menuView->insertAction(ui->menuView->actions()[0], ui->dockWidget->toggleViewAction());
    ui->actionHtmlPreview->setShortcut(QKeySequence(Qt::Key_F5));
    ui->actionFullScreenMode->setShortcut(QKeySequence::FullScreen);
    ui->actionFullScreenMode->setIcon(QIcon("icon-fullscreen.fontawesome"));

    // style menu
    ui->actionDefault->setShortcut(QKeySequence(Qt::ALT + Qt::Key_1));
    ui->actionGithub->setShortcut(QKeySequence(Qt::ALT + Qt::Key_2));
    ui->actionSolarizedLight->setShortcut(QKeySequence(Qt::ALT + Qt::Key_3));
    ui->actionSolarizedDark->setShortcut(QKeySequence(Qt::ALT + Qt::Key_4));
    ui->actionClearness->setShortcut(QKeySequence(Qt::ALT + Qt::Key_5));
    ui->actionClearnessDark->setShortcut(QKeySequence(Qt::ALT + Qt::Key_6));

    // put style actions in a group
    stylesGroup = new QActionGroup(this);
    ui->actionDefault->setActionGroup(stylesGroup);
    ui->actionGithub->setActionGroup(stylesGroup);
    ui->actionSolarizedLight->setActionGroup(stylesGroup);
    ui->actionSolarizedDark->setActionGroup(stylesGroup);
    ui->actionClearness->setActionGroup(stylesGroup);
    ui->actionClearnessDark->setActionGroup(stylesGroup);

    // help menu
    ui->actionMarkdownSyntax->setShortcut(QKeySequence::HelpContents);
}

void MainWindow::setupStatusBar()
{
    // remove border around statusbar widgets
    statusBar()->setStyleSheet("QStatusBar::item { border: 0px solid black }; ");

    // add style label to statusbar
    styleLabel = new QLabel(ui->actionDefault->text(), this);
    styleLabel->setToolTip(tr("Change Preview Style"));
    statusBar()->addPermanentWidget(styleLabel, 1);

    styleLabel->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(styleLabel, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(styleContextMenu(QPoint)));

    // add word count label to statusbar
    wordCountLabel = new QLabel(this);
    wordCountLabel->setAlignment(Qt::AlignHCenter);
    statusBar()->addPermanentWidget(wordCountLabel, 1);

    // add view label to statusbar
    viewLabel = new ActiveLabel(this);
    viewLabel->setAlignment(Qt::AlignRight);
    statusBar()->addPermanentWidget(viewLabel, 1);

    connect(viewLabel, SIGNAL(doubleClicked()),
            this, SLOT(toggleHtmlView()));
}

void MainWindow::setupMarkdownEditor()
{
    // load file that are dropped on the editor
    connect(ui->plainTextEdit, SIGNAL(loadDroppedFile(QString)),
            this, SLOT(load(QString)));

    // synchronize scrollbars
    connect(ui->plainTextEdit->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(scrollValueChanged(int)));

    connect(options, SIGNAL(editorFontChanged(QFont)),
            ui->plainTextEdit, SLOT(editorFontChanged(QFont)));
}

void MainWindow::setupHtmlPreview()
{
    // add our objects everytime JavaScript environment is cleared
    connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(addJavaScriptObject()));

    // restore scrollbar position after content size changed
    connect(ui->webView->page()->mainFrame(), SIGNAL(contentsSizeChanged(QSize)),
            this, SLOT(htmlContentSizeChanged()));

    // load HTML template for live preview from resources
    QFile f(":/template.html");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString htmlTemplate = f.readAll();
        generator->setHtmlTemplate(htmlTemplate);
    }

    // start background HTML preview generator
    connect(generator, SIGNAL(htmlResultReady(QString)),
            this, SLOT(htmlResultReady(QString)));
    connect(generator, SIGNAL(tocResultReady(QString)),
            this, SLOT(tocResultReady(QString)));
    generator->start();
}

void MainWindow::setupHtmlSourceView()
{
    QFont font("Monospace", 10);
    font.setStyleHint(QFont::TypeWriter);
    ui->htmlSourceTextEdit->setFont(font);
    htmlHighlighter = new HtmlHighlighter(ui->htmlSourceTextEdit->document());
}

bool MainWindow::maybeSave()
{
    if (!ui->plainTextEdit->document()->isModified())
        return true;

    if (fileName.startsWith(QLatin1String(":/")))
        return true;

    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.<br>"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;

    return true;
}

void MainWindow::setFileName(const QString &fileName)
{
    this->fileName = fileName;
    ui->plainTextEdit->document()->setModified(false);

    QString shownName = fileName;
    if (shownName.isEmpty()) {
        //: default file name for new markdown documents
        shownName = tr("untitled.md");
    }

    setWindowFilePath(shownName);
    setWindowModified(false);
}

void MainWindow::updateSplitter(bool htmlViewToggled)
{
    // not fully initialized yet?
    if (centralWidget()->size() != ui->splitter->size()) {
        return;
    }

    // calculate new width of left and right pane
    QList<int> childSizes = ui->splitter->sizes();
    int leftWidth = ui->splitter->width() * splitFactor;
    int rightWidth = ui->splitter->width() * (1 - splitFactor);

    bool webViewFolded = ui->webView->isVisible() && childSizes[1] == 0;
    bool htmlSourceFolded = ui->htmlSourceTextEdit->isVisible() && childSizes[2] == 0;

    childSizes[0] = leftWidth;
    if (htmlViewToggled || !webViewFolded) {
        childSizes[1] = rightWidth;
    }
    if (htmlViewToggled || !htmlSourceFolded) {
        childSizes[2] = rightWidth;
    }

    ui->splitter->setSizes(childSizes);
}

void MainWindow::loadCustomStyles()
{
    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
    qDebug() << paths;
    QDir dataPath(paths.first() + QDir::separator() + "styles");
    dataPath.setFilter(QDir::Files);
    if (dataPath.exists()) {
        ui->menuStyles->addSeparator();

        // iterate over all files in the styles subdirectory
        QDirIterator it(dataPath);
        while (it.hasNext()) {
            it.next();

            QString fileName = it.fileName();
            QAction *action = ui->menuStyles->addAction(QFileInfo(fileName).baseName());
            action->setCheckable(true);
            action->setActionGroup(stylesGroup);
            action->setData(it.filePath());

            connect(action, SIGNAL(triggered()),
                    this, SLOT(styleCustomStyle()));
        }
    }
}

void MainWindow::loadDictionaries()
{
    QMap<QString, hunspell::Dictionary> dictionaries = hunspell::SpellChecker::availableDictionaries();

    QActionGroup *dictionariesGroup = new QActionGroup(this);

    QMapIterator<QString, hunspell::Dictionary> it(dictionaries);
    while (it.hasNext()) {
        it.next();

        hunspell::Dictionary dictionary = it.value();

        QAction *action = ui->menuLanguages->addAction(QString("%1 / %2").arg(dictionary.languageName()).arg(dictionary.countryName()), this, SLOT(extrasLanguage()));
        action->setCheckable(true);
        action->setActionGroup(dictionariesGroup);

        QVariant data;
        data.setValue(dictionary);
        action->setData(data);

        if (dictionary.language() == options->dictionaryLanguage()) {
            action->setChecked(true);
            action->trigger();
        }
    }
}

void MainWindow::readSettings()
{
    // restore window size, position and state
    QSettings settings;
    restoreGeometry(settings.value("mainWindow/geometry").toByteArray());
    restoreState(settings.value("mainWindow/windowState").toByteArray());

    // restore recent files menu
    recentFilesMenu->readState();

    options->readSettings();
}

void MainWindow::writeSettings()
{
    options->writeSettings();

    // save recent files menu
    recentFilesMenu->saveState();

    // save window size, position and state
    QSettings settings;
    settings.setValue("mainWindow/geometry", saveGeometry());
    settings.setValue("mainWindow/windowState", saveState());
}
