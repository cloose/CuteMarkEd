#include "htmlhighlighter.h"

HtmlHighlighter::HtmlHighlighter(QTextDocument *document) :
    QSyntaxHighlighter(document)
{
    //keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setForeground(QColor("#6c71c4"));
    keywordFormat.setFontWeight(QFont::Bold);

    HighlightingRule rule;

    QStringList keywords;
    keywords << "<html>" << "</html>"
             << "<head>" << "</head>"
             << "<body>" << "</body>"
             << "<title>" << "</title>"
             << "<script>" << "</script>"
             << "<b>" << "</b>"
             << "<p>" << "</p>"
             << "<i>" << "</i>"
             << "<u>" << "</u>"
             << "<sup>" << "</sup>"
             << "<sub>" << "</sub>"
             << "<h1>" << "</h1>"
             << "<h2>" << "</h2>"
             << "<h3>" << "</h3>"
             << "<h4>" << "</h4>"
             << "<h5>" << "</h5>"
             << "<h6>" << "</h6>"
             << "<small>" << "</small>"
             << "<big>" << "</big>"
             << "<center>" << "</center>"
             << "<nobr>" << "</nobr>"
             << "<blockquote>" << "</blockquote>"
             << "<li>" << "</li>"
             << "<ul>" << "</ul>"
             << "<ol>" << "</ol>"
             << "<dl>" << "</dl>"
             << "<table>" << "</table>"
             << "<td>" << "</td>"
             << "<strike>" << "</strike>";
    foreach(QString keyword, keywords) {
        rule.pattern = QRegExp(keyword);
        rule.format = &keywordFormat;
        highlightingRules.append(rule);
    }
}

void HtmlHighlighter::highlightBlock(const QString &text)
{
    foreach(HighlightingRule rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = text.indexOf(expression);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, *(rule.format));
            index = text.indexOf(expression, index + length);
        }
    }
    setCurrentBlockState(0);
}
