/*
 * Copyright 2014-2015 Christian Loose <christian.loose@hamburg.de>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.  
 *     
 *     (3) The name of the author may not be used to
 *     endorse or promote products derived from this software without
 *     specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "htmltemplate.h"

#include <QFile>
#include <QRegularExpression>

HtmlTemplate::HtmlTemplate()
{
    QFile f(":/template.html");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        htmlTemplate = f.readAll();
    }
}

HtmlTemplate::HtmlTemplate(const QString &templateString) :
	htmlTemplate(templateString)
{
}

QString HtmlTemplate::render(const QString &body, RenderOptions options) const
{
    // add scrollbar synchronization
    options |= Template::ScrollbarSynchronization;

    QString htmlBody(body);

    // Mermaid and highlighting.js don't work nicely together
    // So we need to replace the <code> section by a <div> section
    if (options.testFlag(Template::CodeHighlighting) && options.testFlag(Template::DiagramSupport)) {
        convertDiagramCodeSectionToDiv(htmlBody);
    }

    return renderAsHtml(QString(), htmlBody, options);
}

QString HtmlTemplate::exportAsHtml(const QString &header, const QString &body, RenderOptions options) const
{
    // clear code highlighting option since it depends on the resource file
    options &= ~Template::CodeHighlighting;

    return renderAsHtml(header, body, options);
}

QString HtmlTemplate::renderAsHtml(const QString &header, const QString &body, Template::RenderOptions options) const
{
    if (htmlTemplate.isEmpty()) {
        return body;
    }

    QString htmlHeader = buildHtmlHeader(options);
    htmlHeader += header;

    return QString(htmlTemplate)
            .replace(QLatin1String("<!--__HTML_HEADER__-->"), htmlHeader)
            .replace(QLatin1String("<!--__HTML_CONTENT__-->"), body);
}

QString HtmlTemplate::buildHtmlHeader(RenderOptions options) const
{
    QString header;

    // add javascript for scrollbar synchronization
    if (options.testFlag(Template::ScrollbarSynchronization)) {
        header += "<script type=\"text/javascript\">window.onscroll = function() { synchronizer.webViewScrolled(); }; </script>\n";
    }

    // add MathJax.js script to HTML header
    if (options.testFlag(Template::MathSupport)) {

        // Add MathJax support for inline LaTeX Math
        if (options.testFlag(Template::MathInlineSupport)) {
            header += "<script type=\"text/x-mathjax-config\">MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\\\(','\\\\)']]}});</script>";
        }

        header += "<script type=\"text/javascript\" src=\"http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML\"></script>\n";
    }

    // add Highlight.js script to HTML header
    if (options.testFlag(Template::CodeHighlighting)) {
        header += QString("<link rel=\"stylesheet\" href=\"qrc:/scripts/highlight.js/styles/%1.css\">\n").arg(codeHighlightingStyle());
        header += "<script src=\"qrc:/scripts/highlight.js/highlight.pack.js\"></script>\n";
        header += "<script>hljs.initHighlightingOnLoad();</script>\n";
    }

    // add mermaid.js script to HTML header
    if (options.testFlag(Template::DiagramSupport)) {
        header += "<link rel=\"stylesheet\" href=\"qrc:/scripts/mermaid/mermaid.css\">\n";
        header += "<script src=\"qrc:/scripts/mermaid/mermaid.full.min.js\"></script>\n";
    }

    return header;
}

void HtmlTemplate::convertDiagramCodeSectionToDiv(QString &body) const
{
    static const QRegularExpression rx(QStringLiteral("<pre><code class=\"mermaid\">(.*?)</code></pre>"),
                                       QRegularExpression::DotMatchesEverythingOption);
    body.replace(rx, QStringLiteral("<div class=\"mermaid\">\n\\1</div>"));
}
