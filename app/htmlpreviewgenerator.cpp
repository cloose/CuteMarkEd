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

#include <QFile>

#include <converter/markdownconverter.h>
#include <converter/markdowndocument.h>
#include <converter/discountmarkdownconverter.h>
#include <converter/revealmarkdownconverter.h>

#ifdef ENABLE_HOEDOWN
#include <converter/hoedownmarkdownconverter.h>
#endif

#include "options.h"

HtmlPreviewGenerator::HtmlPreviewGenerator(Options *opt, QObject *parent) :
    QThread(parent),
    options(opt),
    document(0),
    converter(0)
{
    connect(options, SIGNAL(markdownConverterChanged()), SLOT(markdownConverterChanged()));
    markdownConverterChanged();
}

void HtmlPreviewGenerator::setHtmlTemplate(const QString &t)
{
    htmlTemplate = t;
}

bool HtmlPreviewGenerator::isSupported(MarkdownConverter::ConverterOption option) const
{
    return converter->supportedOptions().testFlag(option);
}

void HtmlPreviewGenerator::markdownTextChanged(const QString &text)
{
    // enqueue task to parse the markdown text and generate a new HTML document
    QMutexLocker locker(&tasksMutex);
    tasks.enqueue(text);
    bufferNotEmpty.wakeOne();
}

QString HtmlPreviewGenerator::exportHtml(const QString &styleSheet, const QString &highlightingScript)
{
    if (!document) return QString();

    QString header;
    if (!styleSheet.isEmpty()) {
        header += QString("\n<style>%1</style>").arg(styleSheet);
    }

    if (!highlightingScript.isEmpty()) {
        // FIXME: doesn't really belong here
        QString highlightStyle;
        QFile f(QString(":/scripts/highlight.js/styles/%1.css").arg(codeHighlightingStyle));
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            highlightStyle = f.readAll();
        }

        header += QString("\n<style>%1</style>").arg(highlightStyle);
        header += QString("\n<script>%1</script>").arg(highlightingScript);
        header += "\n<script>hljs.initHighlightingOnLoad();</script>";
    }

    return renderTemplate(header, converter->renderAsHtml(document), QString());
}

void HtmlPreviewGenerator::setMathSupportEnabled(bool enabled)
{
    options->setMathSupportEnabled(enabled);

    // regenerate a HTML document
    generateHtmlFromMarkdown();
}

void HtmlPreviewGenerator::setCodeHighlightingEnabled(bool enabled)
{
    options->setCodeHighlightingEnabled(enabled);

    // regenerate a HTML document
    generateHtmlFromMarkdown();
}

void HtmlPreviewGenerator::setCodeHighlightingStyle(const QString &style)
{
    codeHighlightingStyle = style;

    // regenerate a HTML document
    generateHtmlFromMarkdown();
}

void HtmlPreviewGenerator::markdownConverterChanged()
{
    switch (options->markdownConverter()) {
#ifdef ENABLE_HOEDOWN
    case Options::HoedownMarkdownConverter:
        converter = new HoedownMarkdownConverter();
        break;
#endif

    case Options::RevealMarkdownConverter:
        converter = new RevealMarkdownConverter();
        break;

    case Options::DiscountMarkdownConverter:
    default:
        converter = new DiscountMarkdownConverter();
        break;
    }
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

        // delay processing to see if more tasks are coming
        // (e.g. because the user is typing fast)
        this->msleep(calculateDelay(text));

        // no more new tasks?
        if (tasks.isEmpty()) {
            // delete previous markdown document
            delete document;

            // generate HTML from markdown
            document = converter->createDocument(text, converterOptions());
            generateHtmlFromMarkdown();

            // generate table of contents
            generateTableOfContents();
        }
    }
}

void HtmlPreviewGenerator::generateHtmlFromMarkdown()
{
    if (!document) return;

    QString html = renderTemplate(buildHtmlHeader(), converter->renderAsHtml(document), buildRevealPlugins());
    emit htmlResultReady(html);
}

void HtmlPreviewGenerator::generateTableOfContents()
{
    if (!document) return;

    QString toc = converter->renderAsTableOfContents(document);
    QString styledToc = QString("<html><head>\n<style type=\"text/css\">ul { list-style-type: none; padding: 0; margin-left: 1em; } a { text-decoration: none; }</style>\n</head><body>%1</body></html>").arg(toc);
    emit tocResultReady(styledToc);
}

QString HtmlPreviewGenerator::renderTemplate(const QString &header, const QString &body, const QString &plugins)
{
    if (htmlTemplate.isEmpty()) {
        return body;
    }

    return QString(htmlTemplate)
            .replace(QLatin1String("<!--__HTML_HEADER__-->"), header)
            .replace(QLatin1String("<!--__HTML_CONTENT__-->"), body)
            .replace(QLatin1String("<!--__REVEAL_PLUGINS__-->"), plugins);
}

QString HtmlPreviewGenerator::buildHtmlHeader() const
{
    QString header;

    // add javascript for scrollbar synchronization
    header += "<script type=\"text/javascript\">window.onscroll = function() { mainwin.webViewScrolled(); }; </script>\n";

    // add MathJax.js script to HTML header
    if (options->isMathSupportEnabled()) {
        if (options->markdownConverter() != Options::RevealMarkdownConverter) {
            header += "<script type=\"text/javascript\" src=\"http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML\"></script>\n";
        }
    }

    // add Highlight.js script to HTML header
    if (options->isCodeHighlightingEnabled()) {
        if (options->markdownConverter() != Options::RevealMarkdownConverter) {
            header += QString("<link rel=\"stylesheet\" href=\"qrc:/scripts/highlight.js/styles/%1.css\">\n").arg(codeHighlightingStyle);
            header += "<script src=\"qrc:/scripts/highlight.js/highlight.pack.js\"></script>\n";
            header += "<script>hljs.initHighlightingOnLoad();</script>\n";
        }
    }

    return header;
}

QString HtmlPreviewGenerator::buildRevealPlugins() const
{
    if (options->markdownConverter() != Options::RevealMarkdownConverter) return QString();

    QString plugins;

    // add MathJax.js script as reveal plugin
    if (options->isMathSupportEnabled()) {
        plugins += "{ src: 'https://cdn.jsdelivr.net/reveal.js/2.5.0/plugin/math/math.js', async: true },\n";
    }

    // add Highlight.js script as reveal plugin
    if (options->isCodeHighlightingEnabled()) {
        plugins += "{ src: 'https://cdn.jsdelivr.net/reveal.js/2.5.0/plugin/highlight/highlight.js', async: true, callback: function() { hljs.initHighlightingOnLoad(); } },\n";
    }

    return plugins;
}

MarkdownConverter::ConverterOptions HtmlPreviewGenerator::converterOptions() const
{
    MarkdownConverter::ConverterOptions parserOptionFlags(MarkdownConverter::TableOfContentsOption | MarkdownConverter::NoStyleOption);

    // autolink
    if (options->isAutolinkEnabled()) {
        parserOptionFlags |= MarkdownConverter::AutolinkOption;
    }

    // strikethrough
    if (!options->isStrikethroughEnabled()) {
        parserOptionFlags |= MarkdownConverter::NoStrikethroughOption;
    }

    // alphabetic lists
    if (!options->isAlphabeticListsEnabled()) {
        parserOptionFlags |= MarkdownConverter::NoAlphaListOption;
    }

    // definition lists
    if (!options->isDefinitionListsEnabled()) {
        parserOptionFlags |= MarkdownConverter::NoDefinitionListOption;
    }

    // SmartyPants
    if (!options->isSmartyPantsEnabled()) {
        parserOptionFlags |= MarkdownConverter::NoSmartypantsOption;
    }

    // Footnotes
    if (options->isFootnotesEnabled()) {
        parserOptionFlags |= MarkdownConverter::ExtraFootnoteOption;
    }

    // Superscript
    if (!options->isSuperscriptEnabled()) {
        parserOptionFlags |= MarkdownConverter::NoSuperscriptOption;
    }

    return parserOptionFlags;
}

int HtmlPreviewGenerator::calculateDelay(const QString &text)
{
    const int MINIMUM_DELAY = 50;
    const int MAXIMUM_DELAY = 2000;

    // calculate the processing delay based on amount of characters in the
    // markdown text. The delay is restricted to the interval [50, 2000] milliseconds;
    int delay = qMin(qMax(text.size() / 100, MINIMUM_DELAY), MAXIMUM_DELAY);

    return delay;
}
