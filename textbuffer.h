#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <QtCore/qstring.h>


class TextBuffer
{
public:
    explicit TextBuffer(unsigned int size);
    ~TextBuffer();

    void puts(const QString &text);
    QString gets() const;

    struct buf *buffer() const;

private:
    struct buf *m_buffer;
};

#endif // TEXTBUFFER_H
