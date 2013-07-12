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
    mathSupportEnabled(false),
    codeHighlightingEnabled(false)
{
}

void HtmlPreviewGenerator::enqueue(const QString &text)
{
    QMutexLocker locker(&tasksMutex);
    tasks.enqueue(text);
    bufferNotEmpty.wakeOne();
}

void HtmlPreviewGenerator::setHtmlTemplate(const QString &t)
{
    htmlTemplate = t;
}

void HtmlPreviewGenerator::setMathSupportEnabled(bool enabled)
{
    mathSupportEnabled = enabled;
}

void HtmlPreviewGenerator::setCodeHighlightingEnabled(bool enabled)
{
    codeHighlightingEnabled = enabled;
}

void HtmlPreviewGenerator::setCodeHighlightingStyle(const QString &style)
{
    codeHighlightingStyle = style;
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

            // get next task from queue
            text = tasks.dequeue();
        }

        // end processing?
        if (text.isNull()) {
            return;
        }

        Discount::Parser::ParserOptions parserOptions(Discount::Parser::TableOfContentsOption | Discount::Parser::NoStyleOption);
        if (options->isAutolinkEnabled()) {
            parserOptions |= Discount::Parser::AutolinkOption;
        }
        if (!options->isStrikethroughEnabled()) {
            parserOptions |= Discount::Parser::NoStrikethroughOption;
        }

        // generate HTML from markdown
        Discount::Document document(text, parserOptions);
        QString htmlContent = document.toHtml();
        QString html = renderTemplate(buildHtmlHeader(), htmlContent);
        emit htmlResultReady(html);

        // generate table of contents
        QString toc = document.generateToc();
        emit tocResultReady(toc);
    }
}

QString HtmlPreviewGenerator::renderTemplate(const QString &header, const QString &content)
{
    if (htmlTemplate.isEmpty()) {
        return content;
    }

    return QString(htmlTemplate)
            .replace(QLatin1String("__HTML_HEADER__"), header)
            .replace(QLatin1String("__HTML_CONTENT__"), content);
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
        header += QString("<link rel=\"stylesheet\" href=\"http://yandex.st/highlightjs/7.3/styles/%1.min.css\">").arg(codeHighlightingStyle);
        header += "<script src=\"http://yandex.st/highlightjs/7.3/highlight.min.js\"></script>";
        header += "<script>hljs.initHighlightingOnLoad();</script>";
    }

    return header;
}
