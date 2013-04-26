#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include "pmh_definitions.h"
#include "peg-markdown-highlight/definitions.h"
#include "highlightworkerthread.h"


class MarkdownHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    MarkdownHighlighter(QTextDocument *document);
    ~MarkdownHighlighter();
    
    void setStyles(const QVector<PegMarkdownHighlight::HighlightingStyle> &styles);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private slots:
    void resultReady(pmh_element **elements);

private:
    HighlightWorkerThread *workerThread;
    QVector<PegMarkdownHighlight::HighlightingStyle> highlightingStyles;
};

#endif // MARKDOWNHIGHLIGHTER_H
