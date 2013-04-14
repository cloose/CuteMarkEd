#ifndef MARKDOWNPARSER_H
#define MARKDOWNPARSER_H

#include <QtCore/qstring.h>

class MarkdownParser
{
public:
    MarkdownParser();
    ~MarkdownParser();

    QString renderAsHtml(const QString &text);
};

#endif // MARKDOWNPARSER_H
