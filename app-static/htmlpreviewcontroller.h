/*
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
#ifndef HTMLPREVIEWCONTROLLER_H
#define HTMLPREVIEWCONTROLLER_H

#include <QObject>

class QAction;
class QNetworkDiskCache;
class QWebView;

class HtmlPreviewController : public QObject
{
    Q_OBJECT
public:
    explicit HtmlPreviewController(QWebView *view, QObject *parent = 0);

public slots:
    void zoomInView();
    void zoomOutView();
    void resetZoomOfView();

private:
    void createActions();
    QAction *createAction(const QString &text, const QKeySequence &shortcut);
    void registerActionsWithView();

    void setupNetworkDiskCache();
    
private:
    QWebView *view;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *zoomResetAction;
    QNetworkDiskCache *diskCache;
};

#endif // HTMLPREVIEWCONTROLLER_H

