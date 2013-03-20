#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextDocumentWriter>

#include "markdownparser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    parser(new MarkdownParser())
{
    ui->setupUi(this);
    setupActions();

    setFileName(QString());
}

MainWindow::~MainWindow()
{
    delete parser;
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

void MainWindow::plainTextChanged()
{
    QString code = ui->plainTextEdit->toPlainText();

    QString html = parser->renderAsHtml(code);
    ui->webView->setHtml(html);
    ui->htmlTextEdit->setPlainText(html);
}

void MainWindow::styleChanged(const QString &itemText)
{
    if (itemText == "Default")
        ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl());
    else
        ui->webView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:/" + itemText.toLower() + ".css"));
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
