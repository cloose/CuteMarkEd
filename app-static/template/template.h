/*
 * Copyright 2014-2015 Christian Loose <christian.loose@hamburg.de>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.  
 *     
 *     (3) The name of the author may not be used to
 *     endorse or promote products derived from this software without
 *     specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QString>

class Template
{
public:
    enum RenderOption {
        ScrollbarSynchronization = 0x00000001,
        MathSupport              = 0x00000002,
        CodeHighlighting         = 0x00000004,
        DiagramSupport           = 0x00000008,
        MathInlineSupport        = 0x00000010
    };
    Q_DECLARE_FLAGS(RenderOptions, RenderOption)

    virtual ~Template() {}

    QString codeHighlightingStyle() const { return highlightingStyle; }
    void setCodeHighlightingStyle(const QString &style) { highlightingStyle = style; }

    virtual QString render(const QString &body, RenderOptions options) const = 0;
    virtual QString exportAsHtml(const QString &header, const QString &body, RenderOptions options) const = 0;

private:
    QString highlightingStyle;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Template::RenderOptions)

#endif // TEMPLATE_H
