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
#include "markdownconverter.h"

#include "htmlpostprocessor.h"
#include "textpreprocessor.h"

MarkdownConverter::MarkdownConverter() :
    preprocessor(0),
    postprocessor(0)
{
}

void MarkdownConverter::setTextPreprocessor(const QSharedPointer<TextPreprocessor> &preprocessor)
{
    this->preprocessor = preprocessor;
}

void MarkdownConverter::setHtmlPostprocessor(const QSharedPointer<HtmlPostprocessor> &postprocessor)
{
    this->postprocessor = postprocessor;
}

MarkdownDocument *MarkdownConverter::createDocument(const QString &text, ConverterOptions options)
{
    QString markdownText(text);

    if (preprocessor) {
        preprocessor->processText(markdownText);
    }

    return doCreateDocument(markdownText, options);
}

QString MarkdownConverter::renderAsHtml(MarkdownDocument *document)
{
    QString html = doRenderAsHtml(document);

    if (postprocessor) {
        postprocessor->processHtml(html);
    }

    return html;
}


