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
#ifndef DISCOUNTMARKDOWNCONVERTER_H
#define DISCOUNTMARKDOWNCONVERTER_H

#include "markdownconverter.h"

class DiscountMarkdownConverter : public MarkdownConverter
{
public:
    DiscountMarkdownConverter();

    virtual MarkdownDocument *createDocument(const QString &text, ConverterOptions options);
    virtual QString renderAsHtml(MarkdownDocument *document);
    virtual QString renderAsTableOfContents(MarkdownDocument *document);

    virtual Template *templateRenderer() const;

    virtual ConverterOptions supportedOptions() const;

private:
    unsigned long translateConverterOptions(ConverterOptions options) const;
};

#endif // DISCOUNTMARKDOWNCONVERTER_H
