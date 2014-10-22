/*
 * Copyright 2014 Andreas Reischuck <https://github.com/arBmind>
 * Copyright 2014 Christian Loose <christian.loose@hamburg.de>
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
#ifndef VIEWSYNCHRONIZER_H
#define VIEWSYNCHRONIZER_H

#include <QObject>

class QWebView;
class QPlainTextEdit;


class ViewSynchronizer : public QObject
{
    Q_OBJECT

public:
    ViewSynchronizer(QWebView *webView, QPlainTextEdit *editor, QObject *parent = 0);
    virtual ~ViewSynchronizer() {}

protected:
    QWebView *m_webView;
    QPlainTextEdit *m_editor;
};

#endif // VIEWSYNCHRONIZER_H
