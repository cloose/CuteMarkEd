/*
 * Copyright 2014 Jörg Preiß <joerg.preiss@slesa.de>
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
#include "reveal/revealexporter.h"
#include "reveal/revealoptions.h"
#include "helpers/ziptool.h"
#include <QDesktopServices>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QUrl>
#include <QDebug>

RevealExporter::RevealExporter(const QString& text)
{
    this->code = text;
}

QString RevealExporter::generatePreview()
{
    RevealOptions revealOptions;
    QString indexHtml = readIndexHtml();
    QStringList pages = extractPages();
    QString outputHtml = generateOutput(indexHtml, "Preview", pages, revealOptions);
    return outputHtml;
}

void RevealExporter::run(const QString& destPath, const RevealOptions& revealOptions)
{
    ZipTool zipTool;
    ZipError zipError = zipTool.extract(":/reveal/reveal.zip", destPath);
    if(zipError!=ErrNone) return;

    QString title = extractTitle();
//    qDebug() << "Title: " << title;

    QStringList pages = extractPages();
//    for(int i=0; i<pages.count(); i++)
//        qDebug() << "Page " << i << ": " << pages[i].left(20);

    QString indexHtml = readIndexHtml();
    QString outputHtml = generateOutput(indexHtml, title, pages, revealOptions);
    QString outFile = writeIndexHtml(destPath, outputHtml);
    if(!outFile.isNull())
    {
        QDesktopServices::openUrl(QUrl(outFile));
    }
}

QString RevealExporter::generateOutput(const QString& indexHtml, const QString& title, const QStringList& pages, const RevealOptions& revealOptions)
{
    const QString PAGE_HEADER =
            "<section data-markdown>\n"
            "  <script type=\"text/template\">\n";
    const QString PAGE_FOOTER =
            "  </script>\n"
            "</section>\n"
            "\n"
            "{Pages}\n";

    QString output = indexHtml;
    ReplaceHtmlPlaceholder(output, "{Title}", title);
    ReplaceHtmlPlaceholder(output, "{Author}", revealOptions.author);
    ReplaceHtmlPlaceholder(output, "{Description}", revealOptions.description);
    ReplaceHtmlPlaceholder(output, "{ShowControls}", revealOptions.showControls);
    ReplaceHtmlPlaceholder(output, "{ShowProgress}", revealOptions.showProgress);
    ReplaceHtmlPlaceholder(output, "{UseHistory}", revealOptions.useHistory);
    ReplaceHtmlPlaceholder(output, "{CenterPage}", revealOptions.centerPage);

    for(int i=0; i<pages.count(); i++)
    {
        ReplaceHtmlPlaceholder(output, "{Pages}", PAGE_HEADER + pages[i] + PAGE_FOOTER);
    }
    ReplaceHtmlPlaceholder(output, "{Pages}", "");
    return output;
}

void RevealExporter::ReplaceHtmlPlaceholder(QString &html, const QString &placeholder, const QString &value) const
{
    html = html.replace(placeholder, value, Qt::CaseInsensitive);
}

void RevealExporter::ReplaceHtmlPlaceholder(QString &html, const QString &placeholder, bool value) const
{
    ReplaceHtmlPlaceholder(html, placeholder, value ? QStringLiteral("true") : QStringLiteral("false"));
}

QString RevealExporter::readIndexHtml()
{
    QFile fh(":/reveal/index.html");
    if( !fh.open(QIODevice::ReadOnly|QIODevice::Text) )
    {
        qWarning("RevealExport, could not open index.html");
        return QString::null;
    }
    QString content = QTextStream(&fh).readAll();
    fh.close();
    return content;
}

QString RevealExporter::writeIndexHtml(const QString& destPath, const QString& content)
{
    QString fileName = QString("%1/%2").arg(destPath).arg("index.html");
    QFile fh(fileName);
    if( !fh.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text) )
    {
        qWarning("RevealExport, unable to create output file");
        return QString::null;
    }
    QTextStream(&fh) << content;
    fh.close();
    return fileName;
}

QString RevealExporter::extractTitle()
{
    QString text = this->code;
    int lastIndex = 0;
    for (;;)
    {
        int startIndex = text.indexOf('#', lastIndex);

        // Nothing found?
        if(startIndex<0) break;

        // Found at the end of the text?
        lastIndex = startIndex+1;
        if(lastIndex >= text.length()) break;

        // Found a h2 headline or below?
        if(text[lastIndex]=='#') continue;

        // Found headline, search eol
        int endOfLine = text.indexOf('\n', lastIndex);
        if(endOfLine>0) endOfLine -= 1;
        return text.mid(lastIndex, endOfLine);
    }

    return QString::null;
}

QStringList RevealExporter::extractPages()
{
    QStringList result;

    QString text = this->code;
    int lastPage = -1;
    int lastIndex = 0;

    for (;;)
    {
        int startIndex = text.indexOf("##", lastIndex);
//qDebug() << "Start index " << startIndex;

        // Nothing found?
        if(startIndex<0) break;

        // Found at the end of the text?
        lastIndex = startIndex+2;
        if(lastIndex >= text.length()) break;

        // Found a h3 headline or below?
        if(text[lastIndex]=='#')
        {
//            qDebug("Found h3");
            continue;
        }

//qDebug() << "lastPage? " << lastPage;

        // Found another page, check if there was one before
        if(lastPage>0)
        {
            QString lastText = text.mid(lastPage, startIndex-lastPage-1);
            result.append(lastText);
//qDebug() << "lastText? " << lastText;
        }

        lastPage = startIndex;
//qDebug() << "lastPage now " << lastPage;
    }

    if(lastPage>0) result.append(text.mid(lastPage));
    return result;
}
