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
#ifndef HTMLPOSTPROCESSOR_H
#define HTMLPOSTPROCESSOR_H

class QString;

class HtmlPostprocessor
{
public:
    HtmlPostprocessor();
    virtual ~HtmlPostprocessor() {}

    void setSuccessor(HtmlPostprocessor *successor);

    void processHtml(QString &html);

protected:
    virtual void doProcessHtml(QString &html) = 0;

private:
    HtmlPostprocessor *successor;
};

#endif // HTMLPOSTPROCESSOR_H
