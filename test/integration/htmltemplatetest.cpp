/*
 * Copyright 2015 Christian Loose <christian.loose@hamburg.de>
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
#include "htmltemplatetest.h"

#include <QtTest>

#include <template/htmltemplate.h>
#include "loremipsumtestdata.h"

static const QString HTML_TEMPLATE = QStringLiteral("<html><head><!--__HTML_HEADER__--></head><body><!--__HTML_CONTENT__--></body></html>");
static const QString SCROLL_SCRIPT = QStringLiteral("<script type=\"text/javascript\">window.onscroll = function() { synchronizer.webViewScrolled(); }; </script>");
static const QString MERMAID_CSS   = QStringLiteral("<link rel=\"stylesheet\" href=\"qrc:/scripts/mermaid/mermaid.css\">");
static const QString MERMAID_JS    = QStringLiteral("<script src=\"qrc:/scripts/mermaid/mermaid.full.min.js\"></script>");
static const QString HIGHLIGHT_JS  = QStringLiteral("<link rel=\"stylesheet\" href=\"qrc:/scripts/highlight.js/styles/.css\">\n<script src=\"qrc:/scripts/highlight.js/highlight.pack.js\"></script>\n<script>hljs.initHighlightingOnLoad();</script>");

void HtmlTemplateTest::rendersContentInsideBodyTags()
{
    HtmlTemplate htmlTemplate(HTML_TEMPLATE);

    QString html = htmlTemplate.render("<p>TEST</p>", 0);

    const QString expected = QStringLiteral("<html><head>%1\n</head><body><p>TEST</p></body></html>")
        .arg(SCROLL_SCRIPT);
    QCOMPARE(html, expected);
}

void HtmlTemplateTest::rendersMermaidGraphInsideCodeTags()
{
    HtmlTemplate htmlTemplate(HTML_TEMPLATE);

    QString html = htmlTemplate.render("<pre><code class=\"mermaid\">TEST</code></pre>", HtmlTemplate::DiagramSupport);

    const QString expected = QStringLiteral("<html><head>%1\n%2\n%3\n</head><body><pre><code class=\"mermaid\">TEST</code></pre></body></html>")
        .arg(SCROLL_SCRIPT).arg(MERMAID_CSS).arg(MERMAID_JS);
    QCOMPARE(html, expected);
}

void HtmlTemplateTest::replacesMermaidCodeTagsByDivTagsIfCodeHighlightingEnabled()
{
    HtmlTemplate htmlTemplate(HTML_TEMPLATE);

    QString html = htmlTemplate.render("<pre><code class=\"mermaid\">TEST</code></pre>", HtmlTemplate::DiagramSupport | HtmlTemplate::CodeHighlighting);

    const QString expected = QStringLiteral("<html><head>%1\n%2\n%3\n%4\n</head><body><div class=\"mermaid\">\nTEST</div></body></html>")
        .arg(SCROLL_SCRIPT).arg(HIGHLIGHT_JS).arg(MERMAID_CSS).arg(MERMAID_JS);
    QCOMPARE(html, expected);
}
