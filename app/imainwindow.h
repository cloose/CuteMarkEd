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

/*
 * Interface between presenter and view of the application main window.
 */
class IMainWindow
{
public:
    virtual ~IMainWindow() {}

    virtual void setMarkdownText(const QString &text) = 0;

public slots:
    virtual void setHtml(const QString &html) = 0;
    virtual void setTableOfContents(const QString &toc) = 0;

signals:
    virtual void markdownTextChanged(const QString &text) = 0;
};

Q_DECLARE_INTERFACE(IMainWindow, "IMainWindow")

#endif // IMAINWINDOW_H
