#include "markdownparser.h"

#include "sundown/html.h"

#include "textbuffer.h"

MarkdownParser::MarkdownParser()
    : m_markdown(0)
{
    struct sd_callbacks callbacks;
    struct html_renderopt renderopts;

    sdhtml_renderer(&callbacks, &renderopts, 0);
    int extensions = MKDEXT_TABLES | MKDEXT_LAX_SPACING | MKDEXT_NO_INTRA_EMPHASIS;
    m_markdown = sd_markdown_new(extensions, 16, &callbacks, &renderopts);
}

MarkdownParser::~MarkdownParser()
{
    sd_markdown_free(m_markdown);
}

QString MarkdownParser::renderAsHtml(const QString &text)
{
    if (text.length() > 0)
    {
        TextBuffer input(text.length());
        input.puts(text);

        TextBuffer output(64);

        sd_markdown_render(output.buffer(), input.buffer()->data, input.buffer()->size, m_markdown);

        return output.gets();
    }

    return "";
}
