#include "textbuffer.h"

#include "sundown/buffer.h"

TextBuffer::TextBuffer(unsigned int size)
    : m_buffer(::bufnew(size))
{
}

TextBuffer::~TextBuffer()
{
    ::bufrelease(m_buffer);
}

void TextBuffer::puts(const QString &text)
{
    std::string ss = text.toStdString();
    const char* c_str = ss.c_str();

    ::bufputs(m_buffer, c_str);
}

QString TextBuffer::gets() const
{
    return QString(::bufcstr(m_buffer));
}

struct buf *TextBuffer::buffer() const
{
    return m_buffer;
}
