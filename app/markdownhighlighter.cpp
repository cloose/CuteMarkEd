#include "markdownhighlighter.h"

#include <QDebug>
#include <QFile>
#include <QTextDocument>
#include <QTextLayout>

#include "pmh_parser.h"

#include "peg-markdown-highlight/definitions.h"
using PegMarkdownHighlight::HighlightingStyle;


MarkdownHighlighter::MarkdownHighlighter(QTextDocument *document) :
    QSyntaxHighlighter(document),
    workerThread(new HighlightWorkerThread(this))
{
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

void MarkdownHighlighter::setStyles(const QVector<PegMarkdownHighlight::HighlightingStyle> &styles)
{
    highlightingStyles = styles;
}

void MarkdownHighlighter::highlightBlock(const QString &text)
{
    Q_UNUSED(text)

    if (document()->isEmpty()) {
        return;
    }

    workerThread->enqueue(document()->toPlainText());
}

void MarkdownHighlighter::resultReady(pmh_element **elements)
{
    QTextBlock block = document()->firstBlock();
    while (block.isValid()) {
        block.layout()->clearAdditionalFormats();
        block = block.next();
    }

    if (!elements) {
        qDebug() << "elements is null";
        return;
    }

    // QTextDocument::characterCount returns a value one higher than the
    // actual character count.
    // See: https://bugreports.qt.nokia.com//browse/QTBUG-4841
    // document->toPlainText().length() would give us the correct value
    // but it's probably too slow.
    unsigned long max_offset = document()->characterCount() - 1;

    for (int i = 0; i < highlightingStyles.size(); i++)
    {
        HighlightingStyle style = highlightingStyles.at(i);
        pmh_element *elem_cursor = elements[style.type];
        while (elem_cursor != NULL)
        {
            unsigned long pos = elem_cursor->pos;
            unsigned long end = elem_cursor->end;

            if (end <= pos || max_offset < pos)
            {
                elem_cursor = elem_cursor->next;
                continue;
            }

            if (max_offset < end)
                end = max_offset;

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

    document()->markContentsDirty(0, document()->characterCount());

    pmh_free_elements(elements);
}
