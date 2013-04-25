#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QtGui/QTextCharFormat>

#include "pmh_definitions.h"
#include "pmh_styleparser.h"
#include "highlightworkerthread.h"

struct HighlightingStyle
{
    pmh_element_type type;
    QTextCharFormat format;
};


class MarkdownHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit MarkdownHighlighter(QTextDocument *parent = 0);
    
protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private slots:
    void resultReady(pmh_element **elements);

private:
    void setupDefaultStyle();
    void loadStyleFromStylesheet(const QString &fileName);

private:
    HighlightWorkerThread *workerThread;
    QVector<HighlightingStyle> highlightingStyles;
};

#endif // MARKDOWNHIGHLIGHTER_H
