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
#include "htmlpreviewgenerator.h"

#include "discount/document.h"
#include "discount/parser.h"

#include "options.h"

HtmlPreviewGenerator::HtmlPreviewGenerator(Options *opt, QObject *parent) :
    QThread(parent),
    options(opt),
    document(0),
    mathSupportEnabled(false),
    codeHighlightingEnabled(false)
{
}

void HtmlPreviewGenerator::setHtmlTemplate(const QString &t)
{
    htmlTemplate = t;
}

void HtmlPreviewGenerator::markdownTextChanged(const QString &text)
{
    // enqueue task to parse the markdown text and generate a new HTML document
    QMutexLocker locker(&tasksMutex);
    tasks.enqueue(text);
    bufferNotEmpty.wakeOne();
}

void HtmlPreviewGenerator::setMathSupportEnabled(bool enabled)
{
    mathSupportEnabled = enabled;

    // regenerate a HTML document
    generateHtmlFromMarkdown();
}

void HtmlPreviewGenerator::setCodeHighlightingEnabled(bool enabled)
{
    codeHighlightingEnabled = enabled;

    // regenerate a HTML document
    generateHtmlFromMarkdown();
}

void HtmlPreviewGenerator::setCodeHighlightingStyle(const QString &style)
{
    codeHighlightingStyle = style;

    // regenerate a HTML document
    generateHtmlFromMarkdown();
}

void HtmlPreviewGenerator::run()
{
    forever {
        QString text;

        {
            // wait for new task
            QMutexLocker locker(&tasksMutex);
            while (tasks.count() == 0) {
                bufferNotEmpty.wait(&tasksMutex);
            }

            // get last task from queue and skip all previous tasks
            while (!tasks.isEmpty())
                text = tasks.dequeue();
        }

        // end processing?
        if (text.isNull()) {
            return;
        }

        // delay processing by 100 ms to see if more tasks are coming
        // (e.g. because the user is typing fast)
        this->msleep(100);

        // no more new tasks?
        if (tasks.isEmpty()) {
            // delete previous markdown document
            delete document;

            // generate HTML from markdown
            document = new Discount::Document(text, parserOptions());
            generateHtmlFromMarkdown();

            // generate table of contents
            generateTableOfContents();
        }
    }
}

void HtmlPreviewGenerator::generateHtmlFromMarkdown()
{
    if (!document) return;

    QString html = renderTemplate(buildHtmlHeader(), document->toHtml());
    emit htmlResultReady(html);
}

void HtmlPreviewGenerator::generateTableOfContents()
{
    if (!document) return;

    QString toc = document->generateToc();
    QString styledToc = QString("<html><head>\n<style type=\"text/css\">ul { list-style-type: none; padding: 0; margin-left: 1em; } a { text-decoration: none; }</style>\n</head><body>%1</body></html>").arg(toc);
    emit tocResultReady(styledToc);
}

QString HtmlPreviewGenerator::renderTemplate(const QString &header, const QString &body)
{
    if (htmlTemplate.isEmpty()) {
        return body;
    }

    return QString(htmlTemplate)
            .replace(QLatin1String("__HTML_HEADER__"), header)
            .replace(QLatin1String("__HTML_CONTENT__"), body);
}

QString HtmlPreviewGenerator::buildHtmlHeader() const
{
    QString header;

    // add MathJax.js script to HTML header
    if (mathSupportEnabled) {
        header += "<script type=\"text/javascript\" src=\"http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML\"></script>";
    }

    // add Highlight.js script to HTML header
    if (codeHighlightingEnabled) {
        header += QString("<link rel=\"stylesheet\" href=\"qrc:/scripts/highlight.js/styles/%1.css\">").arg(codeHighlightingStyle);
        header += "<script src=\"qrc:/scripts/highlight.js/highlight.pack.js\"></script>";
        header += "<script>hljs.initHighlightingOnLoad();</script>";
    }

    return header;
}

Discount::Parser::ParserOptions HtmlPreviewGenerator::parserOptions() const
{
    Discount::Parser::ParserOptions parserOptionFlags(Discount::Parser::TableOfContentsOption | Discount::Parser::NoStyleOption);

    // autolink
    if (options->isAutolinkEnabled()) {
        parserOptionFlags |= Discount::Parser::AutolinkOption;
    }

    // strikethrough
    if (!options->isStrikethroughEnabled()) {
        parserOptionFlags |= Discount::Parser::NoStrikethroughOption;
    }

    // alphabetic lists
    if (!options->isAlphabeticListsEnabled()) {
        parserOptionFlags |= Discount::Parser::NoAlphaListOption;
    }

    // definition lists
    if (!options->isDefinitionListsEnabled()) {
        parserOptionFlags |= Discount::Parser::NoDefinitionListOption;
    }

    // SmartyPants
    if (!options->isSmartyPantsEnabled()) {
        parserOptionFlags |= Discount::Parser::NoSmartypantsOption;
    }

    return parserOptionFlags;
}
