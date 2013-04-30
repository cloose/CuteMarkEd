#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QtCore/qstring.h>
#include "parser.h"

namespace Discount
{

class Document
{
public:
    explicit Document(const QString &text);
    ~Document();

    QString toHtml();
    QString generateToc();

private:
    MMIOT *document;
    QString html;
    QString toc;
};

}

#endif // DOCUMENT_H
