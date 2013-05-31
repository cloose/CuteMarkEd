#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QFileDialog>
#include <QIcon>
#include <QLabel>
#include <QMessageBox>
#include <QNetworkDiskCache>
#include <QNetworkProxy>
#include <QPrintDialog>
#include <QPrinter>
#include <QScrollBar>
#include <QStandardPaths>
#include <QTextDocumentWriter>
#include <QTimer>
#include <QWebFrame>
#include <QWebPage>
#include <QWebInspector>

#include "controls/activelabel.h"
#include "controls/findreplacewidget.h"
#include "htmlpreviewgenerator.h"
#include "markdownmanipulator.h"
#include "exporthtmldialog.h"
#include "exportpdfdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    styleLabel(0),
    wordCountLabel(0),
    viewLabel(0),
    generator(new HtmlPreviewGenerator(this)),
    splitFactor(0.5)
{
    ui->setupUi(this);

    setFileName(QString());

    QTimer::singleShot(0, this, SLOT(initializeUI()));
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

void MainWindow::initializeUI()
{
    setupActions();
    setupStatusBar();

    // hide find/replace widget on startup
    ui->findReplaceWidget->hide();

    // inform us when a link in the table of contents view is clicked
    ui->tocWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    ui->dockWidget->close();
    toggleHtmlView();

    connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(addJavaScriptObject()));
    connect(ui->plainTextEdit->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(scrollValueChanged(int)));

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

    // set default style
    styleDefault();

    // load remote javascript and use system proxy configuration
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);

    // FIXME takes too long. provide proxy option per ui
//    QNetworkProxyFactory::setUseSystemConfiguration(true);

    // setup disk cache for network access
    diskCache = new QNetworkDiskCache(this);
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(cacheDir);

//    ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
//    QWebInspector *inspector = new QWebInspector();
//    inspector->setPage(ui->webView->page());
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
    QString name = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              QString(), tr("Markdown Files (*.markdown *.md);;All Files (*)"));
    if (!name.isEmpty()) {
        load(name);
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
        ui->plainTextEdit->document()->setModified(false);
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
            // read used css stylesheet from resources
            QUrl cssUrl = ui->webView->page()->settings()->userStyleSheetUrl();
            QFile f(cssUrl.toString().remove(0, 3));
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

void MainWindow::editSearchReplace()
{
    ui->findReplaceWidget->setTextEdit(ui->plainTextEdit);
    ui->findReplaceWidget->show();
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

void MainWindow::helpAbout()
{
    QMessageBox::about(this, tr("About CuteMarkEd"),
                       tr("<p><b>CuteMarkEd 0.4.0</b><br>Qt-based, free and open source markdown editor with live HTML preview<br>Copyright 2013 Christian Loose</p><p><a href=\"http://cloose.github.io/CuteMarkEd\">http://cloose.github.io/CuteMarkEd</a></p>"));
}

void MainWindow::styleContextMenu(const QPoint &pos)
{
    QList<QAction*> actions;
    actions << ui->actionDefault << ui->actionGithub
            << ui->actionSolarizedLight << ui->actionSolarizedDark
            << ui->actionClearness << ui->actionClearnessDark;

    QMenu *menu = new QMenu();
    menu->addActions(actions);

    menu->exec(styleLabel->mapToGlobal(pos));
}

void MainWindow::toggleHtmlView()
{
    if (viewLabel->text() == tr("HTML preview")) {
        ui->webView->hide();
        ui->htmlSourceTextEdit->show();
        viewLabel->setText(tr("HTML source"));
    } else {
        ui->webView->show();
        ui->htmlSourceTextEdit->hide();
        viewLabel->setText(tr("HTML preview"));
    }

    updateSplitter(true);
}

void MainWindow::plainTextChanged()
{
    QString code = ui->plainTextEdit->toPlainText();

    if (wordCountLabel) {
        int words = ui->plainTextEdit->countWords();
        int lines = ui->plainTextEdit->document()->lineCount();
        int chars = ui->plainTextEdit->document()->characterCount();
        wordCountLabel->setText(tr("%1 words").arg(words));
        wordCountLabel->setToolTip(tr("Lines: %1  Words: %2  Characters: %3").arg(lines).arg(words).arg(chars));
    }

    // generate HTML from markdown
    generator->enqueue(code);
}

void MainWindow::htmlResultReady(const QString &html)
{
    ui->webView->page()->networkAccessManager()->setCache(diskCache);

    // remember scrollbar position
    int scrollBarPos = ui->webView->page()->mainFrame()->scrollBarValue(Qt::Vertical);

    QUrl baseUrl;
    if (fileName.isEmpty()) {
        baseUrl = QUrl::fromLocalFile(qApp->applicationDirPath());
    } else {
        baseUrl = QUrl::fromLocalFile(QFileInfo(fileName).absolutePath() + "/");
    }
    ui->webView->setHtml(html, baseUrl);

    // restore previous scrollbar position
    ui->webView->page()->mainFrame()->setScrollBarValue(Qt::Vertical, scrollBarPos);

    ui->htmlSourceTextEdit->setPlainText(html);
}

void MainWindow::tocResultReady(const QString &toc)
{
    QString styledToc = QString("<html><head>\n<style type=\"text/css\">ul { list-style-type: none; padding: 0; margin-left: 1em; } a { text-decoration: none; }</style>\n</head><body>%1</body></html>").arg(toc);
    ui->tocWebView->setHtml(styledToc);
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
    ui->actionFindReplace->setShortcut(QKeySequence::Find);
    ui->actionFindReplace->setIcon(QIcon("icon-search.fontawesome"));

    // view menu
    ui->menuView->insertAction(ui->menuView->actions()[0], ui->dockWidget->toggleViewAction());

    // style menu
    ui->actionDefault->setShortcut(QKeySequence(Qt::ALT + Qt::Key_1));
    ui->actionGithub->setShortcut(QKeySequence(Qt::ALT + Qt::Key_2));
    ui->actionSolarizedLight->setShortcut(QKeySequence(Qt::ALT + Qt::Key_3));
    ui->actionSolarizedDark->setShortcut(QKeySequence(Qt::ALT + Qt::Key_4));
    ui->actionClearness->setShortcut(QKeySequence(Qt::ALT + Qt::Key_5));
    ui->actionClearnessDark->setShortcut(QKeySequence(Qt::ALT + Qt::Key_6));

    // put style actions in a group
    QActionGroup* group = new QActionGroup( this );
    ui->actionDefault->setActionGroup(group);
    ui->actionGithub->setActionGroup(group);
    ui->actionSolarizedLight->setActionGroup(group);
    ui->actionSolarizedDark->setActionGroup(group);
    ui->actionClearness->setActionGroup(group);
    ui->actionClearnessDark->setActionGroup(group);
}

void MainWindow::setupStatusBar()
{
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
    return true;
}

bool MainWindow::maybeSave()
{
    if (!ui->plainTextEdit->document()->isModified())
        return true;

    if (fileName.startsWith(QLatin1String(":/")))
        return true;

    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
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

    QString shownName;
    if (fileName.isEmpty()) {
        shownName = "untitled.md";
    } else {
        shownName = QFileInfo(fileName).fileName();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg("CuteMarkEd"));
    setWindowModified(false);
}

void MainWindow::updateSplitter(bool htmlViewToggled)
{
    // not fully initialized yet?
    if (centralWidget()->size() != ui->splitter->size()) {
        return;
    }

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

void MainWindow::tocLinkClicked(const QUrl &url)
{
    QString anchor = url.toString().remove("#");
    ui->webView->page()->mainFrame()->scrollToAnchor(anchor);
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
