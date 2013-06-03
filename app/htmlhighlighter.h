#ifndef HTMLHIGHLIGHTER_H
#define HTMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class HtmlHighlighter : public QSyntaxHighlighter
{
public:
    explicit HtmlHighlighter(QTextDocument *document);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat *format;
    };
    QList<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
};

#endif // HTMLHIGHLIGHTER_H
