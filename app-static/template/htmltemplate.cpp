/*
 * Copyright 2014 Christian Loose <christian.loose@hamburg.de>
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
#include "htmltemplate.h"

#include <QFile>

HtmlTemplate::HtmlTemplate()
{
    QFile f(":/template.html");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        htmlTemplate = f.readAll();
    }
}

QString HtmlTemplate::render(const QString &body, RenderOptions options) const
{
    // add scrollbar synchronization
    options |= Template::ScrollbarSynchronization;

    return renderAsHtml(QString(), body, options);
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
        header += "<script type=\"text/javascript\">window.onscroll = function() { mainwin.webViewScrolled(); }; </script>\n";
    }

    // add MathJax.js script to HTML header
    if (options.testFlag(Template::MathSupport)) {
        header += "<script type=\"text/javascript\" src=\"http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML\"></script>\n";
    }

    // add Highlight.js script to HTML header
    if (options.testFlag(Template::CodeHighlighting)) {
        header += QString("<link rel=\"stylesheet\" href=\"qrc:/scripts/highlight.js/styles/%1.css\">\n").arg(codeHighlightingStyle());
        header += "<script src=\"qrc:/scripts/highlight.js/highlight.pack.js\"></script>\n";
        header += "<script>hljs.initHighlightingOnLoad();</script>\n";
    }

    return header;
}
