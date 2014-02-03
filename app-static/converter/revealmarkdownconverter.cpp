#include "revealmarkdownconverter.h"

#include <QStringList>

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

QString RevealMarkdownConverter::renderAsHtml(MarkdownDocument *document)
{
    const QString SLIDE_SEPARATOR = "\n\n---\n\n";
    const QString SLIDE_HEADER = "<section data-markdown>\n"
                                 "  <script type=\"text/template\">\n";
    const QString SLIDE_FOOTER = "  </script>\n"
                                 "</section>\n\n";

    QString html;

    if (document) {
        RevealMarkdownDocument *doc = dynamic_cast<RevealMarkdownDocument*>(document);

        QStringList slides = doc->markdownText.split(SLIDE_SEPARATOR, QString::SkipEmptyParts);
        foreach (QString slide, slides) {
            html += SLIDE_HEADER;
            html += slide;
            html += SLIDE_FOOTER;
        }
    }

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
