#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextDocumentWriter>

#include "htmlpreviewgenerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    generator(new HtmlPreviewGenerator(this))
{
    ui->setupUi(this);

    setupActions();

    // put style actions in a group
    QActionGroup* group = new QActionGroup( this );
    ui->actionDefault->setActionGroup(group);
    ui->actionGithub_like->setActionGroup(group);
    ui->actionClearness->setActionGroup(group);
    ui->actionClearnessDark->setActionGroup(group);

    setFileName(QString());

    // start background HTML preview generator
    connect(generator, SIGNAL(resultReady(QString)),
            this, SLOT(htmlResultReady(QString)));
    generator->start();
}

MainWindow::~MainWindow()
{
    // stop background HTML preview generator
    generator->enqueue(QString());
    generator->wait();
    delete generator;

    delete ui;
}

void MainWindow::fileNew()
{
    ui->plainTextEdit->clear();
    setFileName(QString());
}

void MainWindow::fileOpen()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              QString(), tr("Markdown Files (*.markdown *.md);;All Files (*)"));
    if (!name.isEmpty())
    {
        load(name);
    }
}

void MainWindow::fileSave()
{
    if (fileName.isEmpty())
    {
        fileSaveAs();
        return;
    }

    QTextDocumentWriter writer(fileName, "plaintext");
    bool success = writer.write(ui->plainTextEdit->document());
    if (success)
    {
        ui->plainTextEdit->document()->setModified(false);
    }
}

void MainWindow::fileSaveAs()
{
    QString name = QFileDialog::getSaveFileName(this, tr("Save as..."), QString(),
                                              tr("Markdown Files (*.markdown *.md);;All Files (*)"));
    if (name.isEmpty())
    {
        return;
    }

    setFileName(name);
    fileSave();
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

void MainWindow::styleDefault()
{
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl());
}

void MainWindow::styleGithub()
{
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/GitHub2.css"));
}

void MainWindow::styleClearness()
{
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/Clearness.css"));
}

void MainWindow::styleClearnessDark()
{
    ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/Clearness_Dark.css"));
}

void MainWindow::plainTextChanged()
{
    QString code = ui->plainTextEdit->toPlainText();

    // generate HTML from markdown
    generator->enqueue(code);
}

void MainWindow::htmlResultReady(const QString &html)
{
    ui->webView->setHtml(html);
}

void MainWindow::setupActions()
{
    // file menu
    ui->actionNew->setShortcut(QKeySequence::New);
    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSaveAs->setShortcut(QKeySequence::SaveAs);
    ui->actionExit->setShortcut(QKeySequence::Quit);

    // edit menu
    ui->actionUndo->setShortcut(QKeySequence::Undo);
    ui->actionRedo->setShortcut(QKeySequence::Redo);
}

void MainWindow::setFileName(const QString &fileName)
{
    this->fileName = fileName;

    QString shownName;
    if (fileName.isEmpty()) {
        shownName = "untitled.md";
    } else {
        shownName = QFileInfo(fileName).fileName();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg("CuteMarkEd"));
    setWindowModified(false);
}

void MainWindow::load(const QString &fileName)
{
    if (!QFile::exists(fileName))
    {
        return;
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        return;
    }

    QByteArray content = file.readAll();
    QString text = QString::fromUtf8(content);
    ui->plainTextEdit->setPlainText(text);
}
