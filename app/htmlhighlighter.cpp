#include "htmlhighlighter.h"

HtmlHighlighter::HtmlHighlighter(QTextDocument *document) :
    QSyntaxHighlighter(document)
{
    //keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setForeground(QColor("#6c71c4"));
    keywordFormat.setFontWeight(QFont::Bold);

    HighlightingRule rule;

    QString attrRegExp = "(\\s?(\\S+)=[\"']?((?:.(?![\"']?\\s+(?:\\S+)=|[>\"']))+.)[\"']?\\s?)*";
    QStringList keywords;
    keywords << "<html>" << "</html>"
             << "<head>" << "</head>"
             << "<link" + attrRegExp + ">" << "</link>"
             << "<script" + attrRegExp + ">" << "</script>"
             << "<body>" << "</body>"
             << "<title>" << "</title>"
             << "<b>" << "</b>"
             << "<p" + attrRegExp + ">" << "</p>"
             << "<a" + attrRegExp + ">" << "</a>"
             << "<i>" << "</i>"
             << "<u>" << "</u>"
             << "<sup>" << "</sup>"
             << "<sub>" << "</sub>"
             << "<h1" + attrRegExp + ">" << "</h1>"
             << "<h2" + attrRegExp + ">" << "</h2>"
             << "<h3" + attrRegExp + ">" << "</h3>"
             << "<h4" + attrRegExp + ">" << "</h4>"
             << "<h5" + attrRegExp + ">" << "</h5>"
             << "<h6" + attrRegExp + ">" << "</h6>"
             << "<small>" << "</small>"
             << "<big>" << "</big>"
             << "<center>" << "</center>"
             << "<nobr>" << "</nobr>"
             << "<blockquote>" << "</blockquote>"
             << "<pre>" << "</pre>"
             << "<code>" << "</code>"
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
