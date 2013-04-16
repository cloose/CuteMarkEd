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

private:
    MMIOT *document;
    QString html;
};

}

#endif // DOCUMENT_H
