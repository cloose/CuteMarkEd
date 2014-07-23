/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
