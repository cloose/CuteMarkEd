#include "markdownhighlighter.h"

#include <QDebug>
#include <QFile>
#include <QTextDocument>
#include <QTextLayout>

#include "pmh_parser.h"

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent),
    workerThread(new HighlightWorkerThread(this))
{
    //loadStyleFromStylesheet(":/solarized-dark.style");
    setupDefaultStyle();

    connect(workerThread, SIGNAL(resultReady(pmh_element**)),
            this, SLOT(resultReady(pmh_element**)));
    workerThread->start();
}

void MarkdownHighlighter::highlightBlock(const QString &text)
{
    qDebug() << "highlightBlock";

    Q_UNUSED(text)
    workerThread->enqueue(document()->toPlainText());
}

void MarkdownHighlighter::resultReady(pmh_element **elements)
{
    qDebug() << "resultReady";

    QTextBlock block = document()->firstBlock();
    while (block.isValid()) {
        block.layout()->clearAdditionalFormats();
        block = block.next();
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

#define STY(type, format) highlightingStyles.append((HighlightingStyle){type, format})
void MarkdownHighlighter::setupDefaultStyle()
{
    qDebug() << "setupDefaultStyle";
    highlightingStyles.clear();

    QTextCharFormat header1; header1.setForeground(QBrush(Qt::black));
    header1.setBackground(QBrush(QColor(178,178,207)));
    header1.setFontWeight(QFont::Bold);
    STY(pmh_H1, header1);

    QTextCharFormat header2; header2.setForeground(QBrush(Qt::darkBlue));
    header2.setBackground(QBrush(QColor(204,204,227)));
    header2.setFontWeight(QFont::Bold);
    STY(pmh_H2, header2);

    QTextCharFormat smallerHeaders; smallerHeaders.setForeground(QBrush(Qt::darkBlue));
    smallerHeaders.setBackground(QBrush(QColor(230,230,240)));
    STY(pmh_H3, smallerHeaders);
    STY(pmh_H4, smallerHeaders);
    STY(pmh_H5, smallerHeaders);
    STY(pmh_H6, smallerHeaders);

    QTextCharFormat hrule; hrule.setForeground(QBrush(Qt::darkGray));
    hrule.setBackground(QBrush(Qt::lightGray));
    STY(pmh_HRULE, hrule);

    QTextCharFormat list; list.setForeground(QBrush(Qt::darkMagenta));
    STY(pmh_LIST_BULLET, list);
    STY(pmh_LIST_ENUMERATOR, list);

    QTextCharFormat link; link.setForeground(QBrush(Qt::darkCyan));
    link.setBackground(QBrush(QColor(237,241,242)));
    STY(pmh_LINK, link);
    STY(pmh_AUTO_LINK_URL, link);
    STY(pmh_AUTO_LINK_EMAIL, link);

    QTextCharFormat image; image.setForeground(QBrush(Qt::darkCyan));
    image.setBackground(QBrush(Qt::cyan));
    STY(pmh_IMAGE, image);

    QTextCharFormat ref; ref.setForeground(QBrush(QColor(213,178,178)));
    STY(pmh_REFERENCE, ref);

    QTextCharFormat code; code.setForeground(QBrush(Qt::darkGreen));
    code.setBackground(QBrush(QColor(235,242,235)));
    STY(pmh_CODE, code);
    STY(pmh_VERBATIM, code);

    QTextCharFormat emph; emph.setForeground(QBrush(Qt::darkYellow));
    emph.setFontItalic(true);
    STY(pmh_EMPH, emph);

    QTextCharFormat strong; strong.setForeground(QBrush(QColor(115,50,115)));
    strong.setFontWeight(QFont::Bold);
    STY(pmh_STRONG, strong);

    QTextCharFormat comment; comment.setForeground(QBrush(Qt::gray));
    STY(pmh_COMMENT, comment);

    QTextCharFormat blockquote; blockquote.setForeground(QBrush(Qt::darkRed));
    STY(pmh_BLOCKQUOTE, blockquote);
}

void MarkdownHighlighter::loadStyleFromStylesheet(const QString &fileName)
{
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QByteArray input = f.readAll();
    pmh_style_collection *styles = pmh_parse_styles(input.data(), 0, 0);

    highlightingStyles.clear();
    for (int i = 0; i < pmh_NUM_LANG_TYPES; i++) {
        pmh_style_attribute *attr  = styles->element_styles[i];
        if (!attr)
            continue;

        pmh_element_type type = attr->lang_element_type;
        // TODO!
    }

    // TODO!

    pmh_free_style_collection(styles);
}

