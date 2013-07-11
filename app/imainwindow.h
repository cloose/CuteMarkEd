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
#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H

#include <QString>

class QTextDocument;

class IMainWindow
{
public:
    virtual ~IMainWindow() {}

    virtual QString markdownText() const = 0;
    virtual void setMarkdownText(const QString &text) = 0;
    virtual void setMarkdownTextModified(bool modified) = 0;

    virtual QTextDocument *markdownDocument() const = 0;

    virtual void setHtml(const QString &html) = 0;
    virtual void setTableOfContents(const QString &toc) = 0;

    virtual void updateWindowTitle(const QString &fileName) = 0;

    virtual bool maybeSave() = 0;
};

#endif // IMAINWINDOW_H
