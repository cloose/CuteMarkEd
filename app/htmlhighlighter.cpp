#include "htmlhighlighter.h"

HtmlHighlighter::HtmlHighlighter(QTextDocument *document) :
    QSyntaxHighlighter(document)
{
    keywordFormat.setForeground(QColor("#6c71c4"));
    keywordFormat.setFontWeight(QFont::Bold);

    imageFormat.setForeground(QColor("#cf009a"));

    linkFormat.setForeground(QColor("#4e279a"));

    HighlightingRule rule;

    QString htmlTagRegExp = "<(/?)(%1)[^>]*(/?)>";
    QStringList keywords;
    keywords << htmlTagRegExp.arg("html")
             << "<head>" << "</head>"
             << htmlTagRegExp.arg("link")
             << htmlTagRegExp.arg("script")
             << "<body>" << "</body>"
             << "<title>" << "</title>"
             << "<b>" << "</b>"
             << htmlTagRegExp.arg("p")
             << "<i>" << "</i>"
             << "<u>" << "</u>"
             << "<sup>" << "</sup>"
             << "<sub>" << "</sub>"
             << htmlTagRegExp.arg("h1")
             << htmlTagRegExp.arg("h2")
             << htmlTagRegExp.arg("h3")
             << htmlTagRegExp.arg("h4")
             << htmlTagRegExp.arg("h5")
             << htmlTagRegExp.arg("h6")
             << htmlTagRegExp.arg("br")
             << htmlTagRegExp.arg("hr")
             << "<small>" << "</small>"
             << "<big>" << "</big>"
             << "<strong>" << "</strong>"
             << "<em>" << "</em>"
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
             << "<thead>" << "</thead>"
             << "<tbody>" << "</tbody>"
             << htmlTagRegExp.arg("th")
             << htmlTagRegExp.arg("td")
             << htmlTagRegExp.arg("tr")
             << "<strike>" << "</strike>"
             << "<del>" << "</del>";

    foreach(QString keyword, keywords) {
        rule.pattern = QRegExp(keyword);
        rule.format = &keywordFormat;
        highlightingRules.append(rule);
    }

    rule.pattern = QRegExp(htmlTagRegExp.arg("img"));
    rule.format = &imageFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp(htmlTagRegExp.arg("a"));
    rule.format = &linkFormat;
    highlightingRules.append(rule);
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
