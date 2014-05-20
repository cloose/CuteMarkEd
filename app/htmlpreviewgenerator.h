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
#ifndef HTMLPREVIEWGENERATOR_H
#define HTMLPREVIEWGENERATOR_H

#include <QtCore/qthread.h>
#include <QtCore/qqueue.h>
#include <QtCore/qmutex.h>
#include <QtCore/qwaitcondition.h>

#include <converter/markdownconverter.h>
#include <template/template.h>

class MarkdownDocument;
class Options;

class HtmlPreviewGenerator : public QThread
{
    Q_OBJECT

public:
    explicit HtmlPreviewGenerator(Options *opt, QObject *parent = 0);
    
    bool isSupported(MarkdownConverter::ConverterOption option) const;

public slots:
    void markdownTextChanged(const QString &text);
    QString exportHtml(const QString &styleSheet, const QString &highlightingScript);

    void setMathSupportEnabled(bool enabled);
    void setCodeHighlightingEnabled(bool enabled);
    void setCodeHighlightingStyle(const QString &style);

    void markdownConverterChanged();

signals:
    void htmlResultReady(const QString &html);
    void tocResultReady(const QString &toc);

protected:
    virtual void run();

private:
    void generateHtmlFromMarkdown();
    void generateTableOfContents();
    MarkdownConverter::ConverterOptions converterOptions() const;
    Template::RenderOptions renderOptions() const;
    int calculateDelay(const QString &text);

private:
    Options *options;
    MarkdownDocument *document;
    MarkdownConverter *converter;
    QQueue<QString> tasks;
    QMutex tasksMutex;
    QWaitCondition bufferNotEmpty;
};

#endif // HTMLPREVIEWGENERATOR_H
