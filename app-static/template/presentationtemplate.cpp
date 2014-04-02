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
#include "presentationtemplate.h"

#include <QFile>

PresentationTemplate::PresentationTemplate()
{
    QFile f(":/template_presentation.html");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        presentationTemplate = f.readAll();
    }
}

QString PresentationTemplate::render(const QString &body, RenderOptions options) const
{
    if (presentationTemplate.isEmpty()) {
        return body;
    }

    return QString(presentationTemplate)
            .replace(QLatin1String("<!--__HTML_HEADER__-->"), QString())
            .replace(QLatin1String("<!--__HTML_CONTENT__-->"), body)
            .replace(QLatin1String("<!--__REVEAL_PLUGINS__-->"), buildRevealPlugins(options));
}

QString PresentationTemplate::exportAsHtml(const QString &, const QString &body, RenderOptions options) const
{
    return render(body, options);
}

QString PresentationTemplate::buildRevealPlugins(RenderOptions options) const
{
    QString plugins;

    // add MathJax.js script as reveal plugin
    if (options.testFlag(Template::MathSupport)) {
        plugins += "{ src: 'https://cdn.jsdelivr.net/reveal.js/2.5.0/plugin/math/math.js', async: true },\n";
    }

    // add Highlight.js script as reveal plugin
    if (options.testFlag(Template::CodeHighlighting)) {
        plugins += "{ src: 'https://cdn.jsdelivr.net/reveal.js/2.5.0/plugin/highlight/highlight.js', async: true, callback: function() { hljs.initHighlightingOnLoad(); } },\n";
    }

    return plugins;
}
