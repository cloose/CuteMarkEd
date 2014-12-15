/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
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
#ifndef MARKDOWNCONVERTER_H
#define MARKDOWNCONVERTER_H

#include <QString>

class MarkdownDocument;
class Options;
class Template;

class MarkdownConverter
{
public:
    enum ConverterOption {
        NoLinksOption          = 0x00000001, /* don't do link processing, block <a> tags  */
        NoImagesOption         = 0x00000002, /* don't do image processing, block <img> */
        NoSmartypantsOption    = 0x00000004, /* don't run smartypants() */
        NoHtmlOption           = 0x00000008, /* don't allow raw html through AT ALL */
        NoSuperscriptOption    = 0x00000100, /* don't process a^2 as superscript(<sup>) */
        NoTablesOption         = 0x00000400, /* disallow tables */
        NoStrikethroughOption  = 0x00000800, /* forbid ~~strikethrough~~ */
        TableOfContentsOption  = 0x00001000, /* do table-of-contents processing */
        AutolinkOption         = 0x00004000, /* make http://foo.com link even without <>s */
        NoHeaderOption         = 0x00010000, /* don't process header blocks */
        NoDivQuoteOption       = 0x00040000, /* forbid >%class% blocks */
        NoAlphaListOption      = 0x00080000, /* forbid alphabetic lists */
        NoDefinitionListOption = 0x00100000, /* forbid definition lists */
        ExtraFootnoteOption    = 0x00200000, /* enable markdown extra-style footnotes */
        NoStyleOption          = 0x00400000  /* don't extract <style> blocks */
    };
    Q_DECLARE_FLAGS(ConverterOptions, ConverterOption)

    virtual ~MarkdownConverter() {}

    virtual MarkdownDocument *createDocument(const QString &text, ConverterOptions options) = 0;
    virtual QString renderAsHtml(MarkdownDocument *document) = 0;
    virtual QString renderAsTableOfContents(MarkdownDocument *document) = 0;

    virtual Template *templateRenderer() const = 0;

    virtual ConverterOptions supportedOptions() const = 0;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MarkdownConverter::ConverterOptions)

#endif // MARKDOWNCONVERTER_H
