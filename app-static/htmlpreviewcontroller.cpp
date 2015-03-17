/*
 * Copyright 2014-2015 Christian Loose <christian.loose@hamburg.de>
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
#include "htmlpreviewcontroller.h"

#include <QAction>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QWebView>

static const qreal ZOOM_CHANGE_VALUE = 0.1;

HtmlPreviewController::HtmlPreviewController(QWebView *view, QObject *parent) :
    QObject(parent),
    view(view),
    zoomInAction(0),
    zoomOutAction(0),
    zoomResetAction(0),
    diskCache(new QNetworkDiskCache(this))
{
    createActions();
    registerActionsWithView();

    // use registered actions as custom context menu
    view->setContextMenuPolicy(Qt::ActionsContextMenu);

    setupNetworkDiskCache();
}

void HtmlPreviewController::createActions()
{
    zoomInAction = createAction(tr("Zoom &In"), QKeySequence(Qt::CTRL | Qt::Key_Plus));
    connect(zoomInAction, SIGNAL(triggered()), 
            this, SLOT(zoomInView()));

    zoomOutAction = createAction(tr("Zoom &Out"), QKeySequence(Qt::CTRL | Qt::Key_Minus));
    connect(zoomOutAction, SIGNAL(triggered()),
            this, SLOT(zoomOutView()));

    zoomResetAction = createAction(tr("Reset &Zoom"), QKeySequence(Qt::CTRL | Qt::Key_0));
    connect(zoomResetAction, SIGNAL(triggered()),
            this, SLOT(resetZoomOfView()));
}

QAction *HtmlPreviewController::createAction(const QString &text, const QKeySequence &shortcut)
{
    QAction *action = new QAction(text, this);
    action->setShortcut(shortcut);
    return action;
}

void HtmlPreviewController::registerActionsWithView()
{
    view->addAction(view->pageAction(QWebPage::Copy));
    view->addAction(view->pageAction(QWebPage::InspectElement));
    view->addAction(zoomInAction);
    view->addAction(zoomOutAction);
    view->addAction(zoomResetAction);
}

void HtmlPreviewController::setupNetworkDiskCache()
{
    // setup disk cache for network access
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(cacheDir);

    view->page()->networkAccessManager()->setCache(diskCache);
}

void HtmlPreviewController::zoomInView()
{
    view->setZoomFactor(view->zoomFactor() + ZOOM_CHANGE_VALUE);
}

void HtmlPreviewController::zoomOutView()
{
    view->setZoomFactor(view->zoomFactor() - ZOOM_CHANGE_VALUE);
}

void HtmlPreviewController::resetZoomOfView()
{
    view->setZoomFactor(1.0);
}

