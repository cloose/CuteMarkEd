#ifndef STYLEPARSER_H
#define STYLEPARSER_H

#include "definitions.h"
#include <pmh_styleparser.h>


namespace PegMarkdownHighlight
{

class StyleParser
{
public:
    explicit StyleParser(const QString& styleSheet);
    ~StyleParser();

    QVector<HighlightingStyle> highlightingStyles(QFont baseFont) const;
    QPalette editorPalette() const;

    void handleStyleParsingError(char *errorMessage, int lineNumber);

private:
    pmh_style_collection *styles;
    QList<QPair<int, QString> > styleParsingErrorList;
};

}

#endif // STYLEPARSER_H
