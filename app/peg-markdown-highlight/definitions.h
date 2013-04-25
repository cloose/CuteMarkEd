#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <pmh_definitions.h>
#include <QtGui/QTextCharFormat>


namespace PegMarkdownHighlight
{

struct HighlightingStyle
{
    pmh_element_type type;
    QTextCharFormat format;
};

}

#endif // DEFINITIONS_H
