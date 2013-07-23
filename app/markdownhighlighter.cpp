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
#include "markdownhighlighter.h"

#include <QDebug>
#include <QFile>
#include <QTextDocument>
#include <QTextLayout>

#include "pmh_parser.h"

#include "peg-markdown-highlight/definitions.h"
using PegMarkdownHighlight::HighlightingStyle;

#include "hunspell/spellchecker.h"
using hunspell::SpellChecker;

#include <QDebug>


MarkdownHighlighter::MarkdownHighlighter(QTextDocument *document, hunspell::SpellChecker *spellChecker) :
    QSyntaxHighlighter(document),
    workerThread(new HighlightWorkerThread(this))
{
    this->spellChecker = spellChecker;

    // QTextCharFormat::SpellCheckUnderline has issues with Qt 5.
    spellFormat.setUnderlineStyle(QTextCharFormat::WaveUnderline);
    spellFormat.setUnderlineColor(Qt::red);

    connect(workerThread, SIGNAL(resultReady(pmh_element**)),
            this, SLOT(resultReady(pmh_element**)));
    workerThread->start();
}

MarkdownHighlighter::~MarkdownHighlighter()
{
    // stop background worker thread
    workerThread->enqueue(QString());
    workerThread->wait();
    delete workerThread;
}

void MarkdownHighlighter::reset()
{
    previousText.clear();
}

void MarkdownHighlighter::setStyles(const QVector<PegMarkdownHighlight::HighlightingStyle> &styles)
{
    highlightingStyles = styles;
    reset();
}

void MarkdownHighlighter::setSpellingCheckEnabled(bool enabled)
{
    spellingCheckEnabled = enabled;
}

void MarkdownHighlighter::highlightBlock(const QString &textBlock)
{
    if (document()->isEmpty()) {
        return;
    }

    // check spelling of passed text block
    if (spellingCheckEnabled) {
        QStringList wordList = textBlock.split(QRegExp("\\W+"), QString::SkipEmptyParts);
        int index = 0;
        foreach (QString word, wordList) {
           index = textBlock.indexOf(word, index);

           if (!spellChecker->isCorrect(word)) {
               setFormat(index, word.length(), spellFormat);
           }
           index += word.length();
        }
    }

    QString text = document()->toPlainText();

    // document changed since last call?
    if (text == previousText) {
        return;
    }

    workerThread->enqueue(text);

    previousText = text;
}

void MarkdownHighlighter::resultReady(pmh_element **elements)
{
    if (!elements) {
        qDebug() << "elements is null";
        return;
    }

    // The QTextDocument contains an additional single paragraph separator (unicode 0x2029).
    // https://bugreports.qt-project.org/browse/QTBUG-4841
    unsigned long max_offset = document()->characterCount() - 1;

    for (int i = 0; i < highlightingStyles.size(); i++) {
        HighlightingStyle style = highlightingStyles.at(i);
        pmh_element *elem_cursor = elements[style.type];
        while (elem_cursor != NULL) {
            unsigned long pos = elem_cursor->pos;
            unsigned long end = elem_cursor->end;

            if (end <= pos || max_offset < pos) {
                elem_cursor = elem_cursor->next;
                continue;
            }

            if (max_offset < end) {
                end = max_offset;
            }

            // "The QTextLayout object can only be modified from the
            // documentChanged implementation of a QAbstractTextDocumentLayout
            // subclass. Any changes applied from the outside cause undefined
            // behavior." -- we are breaking this rule here. There might be
            // a better (more correct) way to do this.

            int startBlockNum = document()->findBlock(pos).blockNumber();
            int endBlockNum = document()->findBlock(end).blockNumber();
            for (int j = startBlockNum; j <= endBlockNum; j++)
            {
                QTextBlock block = document()->findBlockByNumber(j);

                QTextLayout *layout = block.layout();
                QList<QTextLayout::FormatRange> list = layout->additionalFormats();
                int blockpos = block.position();
                QTextLayout::FormatRange r;
                r.format = style.format;

                if (/*_makeLinksClickable
                    &&*/ (elem_cursor->type == pmh_LINK
                        || elem_cursor->type == pmh_AUTO_LINK_URL
                        || elem_cursor->type == pmh_AUTO_LINK_EMAIL
                        || elem_cursor->type == pmh_REFERENCE)
                    && elem_cursor->address != NULL)
                {
                    QString address(elem_cursor->address);
                    if (elem_cursor->type == pmh_AUTO_LINK_EMAIL && !address.startsWith("mailto:"))
                        address = "mailto:" + address;
                    QTextCharFormat linkFormat(r.format);
                    linkFormat.setAnchor(true);
                    linkFormat.setAnchorHref(address);
                    linkFormat.setToolTip(address);
                    r.format = linkFormat;
                }

                if (j == startBlockNum) {
                    r.start = pos - blockpos;
                    r.length = (startBlockNum == endBlockNum)
                                ? end - pos
                                : block.length() - r.start;
                } else if (j == endBlockNum) {
                    r.start = 0;
                    r.length = end - blockpos;
                } else {
                    r.start = 0;
                    r.length = block.length();
                }

                list.append(r);
                layout->setAdditionalFormats(list);
            }

            elem_cursor = elem_cursor->next;
        }
    }

    // mark complete document as dirty
    document()->markContentsDirty(0, document()->characterCount());

    // free highlighting elements
    pmh_free_elements(elements);
}
