#ifndef PARSER_H
#define PARSER_H

#include <QtCore/qstring.h>

extern "C" {
#ifdef Q_OS_WIN
#include <Windows.h>
#endif
#include <mkdio.h>
}

namespace Discount
{

class Parser
{
public:
    Parser();
    ~Parser();

    static MMIOT* parseString(const QString &text);
    static QString renderAsHtml(MMIOT *document);
    static QString generateToc(MMIOT *document);

    static void cleanup(MMIOT *document);
};

}

#endif // PARSER_H
