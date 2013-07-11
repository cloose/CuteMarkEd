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
#include "mainwindowpresenter.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QTextDocumentWriter>
#include <QUrl>

#include "imainwindow.h"
#include "htmlpreviewgenerator.h"
#include "markdownmanipulator.h"
#include "controls/recentfilesmenu.h"

MainWindowPresenter::MainWindowPresenter(IMainWindow *view, QObject *parent) :
    QObject(parent),
    generator(new HtmlPreviewGenerator(this)),
    manipulator(0),
    recentFilesMenu(0)
{
    this->view = view;
}

MainWindowPresenter::~MainWindowPresenter()
{
    delete manipulator;

    // stop background HTML preview generator
    generator->enqueue(QString());
    generator->wait();
    delete generator;
}

void MainWindowPresenter::onViewReady()
{
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

QUrl MainWindowPresenter::previewBaseUrl() const
{
    if (m_fileName.isEmpty()) {
        return QUrl::fromLocalFile(qApp->applicationDirPath());
    } else {
        return QUrl::fromLocalFile(QFileInfo(m_fileName).absolutePath() + "/");
    }
}

void MainWindowPresenter::setMarkdownManipulator(MarkdownManipulator *manipulator)
{
    this->manipulator = manipulator;
}

void MainWindowPresenter::setRecentFilesMenu(RecentFilesMenu *menu)
{
    recentFilesMenu = menu;

    connect(recentFilesMenu, SIGNAL(recentFileTriggered(QString)),
            this, SLOT(openRecentFile(QString)));
}

void MainWindowPresenter::setMathSupportEnabled(bool enabled)
{
    generator->setMathSupportEnabled(enabled);
    markdownTextChanged();
}

void MainWindowPresenter::setCodeHighlightingEnabled(bool enabled)
{
    generator->setCodeHighlightingEnabled(enabled);
    markdownTextChanged();
}

void MainWindowPresenter::setCodeHighlightingStyle(const QString &style)
{
    generator->setCodeHighlightingStyle(style);
    markdownTextChanged();
}

QString MainWindowPresenter::fileName() const
{
    return m_fileName;
}

void MainWindowPresenter::setFileName(const QString &fileName)
{
    m_fileName = fileName;
    view->updateWindowTitle(fileName);
}

void MainWindowPresenter::readSettings()
{
    if (recentFilesMenu) {
        // restore recent files menu
        recentFilesMenu->readState();
    }
}

void MainWindowPresenter::writeSettings()
{
    if (recentFilesMenu) {
        // save recent files menu
        recentFilesMenu->saveState();
    }
}

bool MainWindowPresenter::loadFile(const QString &fileName)
{
    if (!QFile::exists(fileName)) {
        return false;
    }

    // open file
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    // read content from file
    QByteArray content = file.readAll();
    QString text = QString::fromUtf8(content);
    view->setMarkdownText(text);

    // remember name of new file
    setFileName(fileName);

    // add to recent files
    addToRecentFiles(fileName);

    return true;
}

bool MainWindowPresenter::saveFile(const QString &fileName)
{
    // save markdown document
    QTextDocumentWriter writer(fileName, "plaintext");
    bool success = writer.write(view->markdownDocument());

    if (success) {
        // set status to unmodified
        view->setMarkdownTextModified(false);

        // add to recent file list
        addToRecentFiles(fileName);
    }

    return success;
}

void MainWindowPresenter::editStrong()
{
    manipulator->wrapSelectedText("**");
}

void MainWindowPresenter::editEmphasize()
{
    manipulator->wrapSelectedText("*");
}

void MainWindowPresenter::editStrikethrough()
{
    manipulator->wrapSelectedText("~~");
}

void MainWindowPresenter::editInlineCode()
{
    manipulator->wrapSelectedText("`");
}

void MainWindowPresenter::editCenterParagraph()
{
    manipulator->wrapCurrentParagraph("->", "<-");
}

void MainWindowPresenter::editHardLinebreak()
{
    manipulator->appendToLine("  \n");
}

void MainWindowPresenter::editBlockquote()
{
    manipulator->prependToLine('>');
}

void MainWindowPresenter::markdownTextChanged()
{
    // generate HTML from markdown
    QString markdownText = view->markdownText();
    generator->enqueue(markdownText);
}

void MainWindowPresenter::htmlResultReady(const QString &html)
{
    view->setHtml(html);
}

void MainWindowPresenter::tocResultReady(const QString &toc)
{
    QString styledToc = QString("<html><head>\n<style type=\"text/css\">ul { list-style-type: none; padding: 0; margin-left: 1em; } a { text-decoration: none; }</style>\n</head><body>%1</body></html>").arg(toc);
    view->setTableOfContents(styledToc);
}

void MainWindowPresenter::openRecentFile(const QString &fileName)
{
    if (view->maybeSave()) {
        loadFile(fileName);
    }
}

void MainWindowPresenter::addToRecentFiles(const QString &fileName)
{
    if (recentFilesMenu) {
        recentFilesMenu->addFile(QDir::toNativeSeparators(fileName));
    }
}
