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
#include <QFileInfo>
#include <QFile>
#include <QUrl>

#include "htmlpreviewgenerator.h"
#include "imainwindow.h"

MainWindowPresenter::MainWindowPresenter(QObject *view, Options *options) :
    QObject(view),
    generator(new HtmlPreviewGenerator(options, this))
{
    // generate a new HTML document from the markdown text if it changed
    connect(view, SIGNAL(markdownTextChanged(QString)),
            generator, SLOT(markdownTextChanged(QString)));

    // show generated HTML and TOC
    connect(generator, SIGNAL(htmlResultReady(QString)),
            view, SLOT(setHtml(QString)));
    connect(generator, SIGNAL(tocResultReady(QString)),
            view, SLOT(setTableOfContents(QString)));

    this->view = qobject_cast<IMainWindow*>(view);
}

MainWindowPresenter::~MainWindowPresenter()
{
    // stop background HTML preview generator
    generator->markdownTextChanged(QString());
    generator->wait();
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
    generator->start();
}

QString MainWindowPresenter::fileName() const
{
    return m_fileName;
}

void MainWindowPresenter::setFileName(const QString &fileName)
{
    m_fileName = fileName;
    emit fileNameChanged(fileName);
}

QUrl MainWindowPresenter::previewBaseUrl() const
{
    // determine base URL for HTML preview
    if (m_fileName.isEmpty()) {
        return QUrl::fromLocalFile(qApp->applicationDirPath());
    } else {
        return QUrl::fromLocalFile(QFileInfo(m_fileName).absolutePath() + "/");
    }
}

bool MainWindowPresenter::loadFile(const QString &fileName)
{
    if (fileName.isEmpty()) {
        return false;
    }

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

    return true;
}

void MainWindowPresenter::setMathSupportEnabled(bool enabled)
{
    generator->setMathSupportEnabled(enabled);
}

void MainWindowPresenter::setCodeHighlightingEnabled(bool enabled)
{
    generator->setCodeHighlightingEnabled(enabled);
}

void MainWindowPresenter::setCodeHighlightingStyle(const QString &style)
{
    generator->setCodeHighlightingStyle(style);
}
