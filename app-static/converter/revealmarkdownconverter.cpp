#include "revealmarkdownconverter.h"

#include "markdowndocument.h"

class RevealMarkdownDocument : public MarkdownDocument
{
public:
    QString markdownText;
};

RevealMarkdownConverter::RevealMarkdownConverter()
{
}

MarkdownDocument *RevealMarkdownConverter::createDocument(const QString &text, MarkdownConverter::ConverterOptions options)
{
    RevealMarkdownDocument *doc = new RevealMarkdownDocument();
    doc->markdownText = text;
    return doc;
}

#include <QDebug>
#include <QStringList>
#include <QRegularExpression>
QString RevealMarkdownConverter::renderAsHtml(MarkdownDocument *document)
{
    QString html = QStringLiteral("<div class=\"reveal\">\n");
    html += QStringLiteral("<div class=\"slides\">\n");

    if (document) {
        RevealMarkdownDocument *doc = dynamic_cast<RevealMarkdownDocument*>(document);

        QRegularExpression rx("(#{2})[ \t]*(.+?)[ \t]*#*\n+");
//        QRegularExpressionMatch match = rx.match(doc->markdownText);
//        while (match.hasMatch()) {
//            qDebug() << match.capturedTexts() << match.capturedLength()+1;

//            html += QStringLiteral("<section data-markdown>\n");
//            html += QStringLiteral("<script type=\"text/template\">\n");

//            html += match.captured(0);

//            html += QStringLiteral("</script>\n");
//            html += QStringLiteral("</section>\n\n");

//            match = rx.match(doc->markdownText, match.capturedLength()+1);
//        }
        QRegularExpressionMatchIterator it = rx.globalMatch(doc->markdownText);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            qDebug() << match.capturedTexts() << match.capturedLength()+1;

            html += QStringLiteral("<section data-markdown>\n");
            html += QStringLiteral("<script type=\"text/template\">\n");

            html += match.captured(0);

            html += QStringLiteral("</script>\n");
            html += QStringLiteral("</section>\n\n");

//            match = rx.match(doc->markdownText, match.capturedLength()+1);
        }

//        html += doc->markdownText;

    }

    html += QStringLiteral("</div>\n");
    html += QStringLiteral("</div>\n");
    html += QStringLiteral("<script src=\"http://cdn.jsdelivr.net/reveal.js/2.5.0/lib/js/head.min.js\"></script>\n");
    html += QStringLiteral("<script src=\"http://cdn.jsdelivr.net/reveal.js/2.5.0/js/reveal.min.js\"></script>\n");
    html += QStringLiteral("<script>Reveal.initialize({\n");
    html += QStringLiteral("dependencies: [\n");
    html += QStringLiteral("{ src: 'http://cdn.jsdelivr.net/reveal.js/2.5.0/plugin/markdown/marked.js', condition: function() { return !!document.querySelector( '[data-markdown]' ); } },\n");
    html += QStringLiteral("{ src: 'http://cdn.jsdelivr.net/reveal.js/2.5.0/plugin/markdown/markdown.js', condition: function() { return !!document.querySelector( '[data-markdown]' ); } },\n");
    html += QStringLiteral("]});</script>\n");

    return html;
}

QString RevealMarkdownConverter::renderAsTableOfContents(MarkdownDocument *document)
{
    return QString();
}

MarkdownConverter::ConverterOptions RevealMarkdownConverter::supportedOptions() const
{
    return MarkdownConverter::AutolinkOption |
           MarkdownConverter::NoStrikethroughOption |
           MarkdownConverter::NoAlphaListOption |
           MarkdownConverter::NoDefinitionListOption |
           MarkdownConverter::NoSmartypantsOption |
           MarkdownConverter::ExtraFootnoteOption |
           MarkdownConverter::NoSuperscriptOption;
}
