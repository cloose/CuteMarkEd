#ifndef MARKDOWNPARSER_H
#define MARKDOWNPARSER_H

#include <QtCore/qstring.h>

class MarkdownParser
{
public:
    MarkdownParser();
    ~MarkdownParser();

    QString renderAsHtml(const QString &text);

private:
    struct sd_markdown *m_markdown;
};

#endif // MARKDOWNPARSER_H
