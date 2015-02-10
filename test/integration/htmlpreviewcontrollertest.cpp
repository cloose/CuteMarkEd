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
#include "htmlpreviewcontrollertest.h"

#include <QtTest>
#include <QWebView>

#include "htmlpreviewcontroller.h"

void HtmlPreviewControllerTest::initTestCase()
{
    webView = new QWebView();
    controller = new HtmlPreviewController(webView);

    webView->show();
    QTest::qWaitForWindowExposed(webView);
    webView->activateWindow();
    QTest::qWaitForWindowActive(webView);
}

void HtmlPreviewControllerTest::cleanupTestCase()
{
    delete controller;
    delete webView;
}

void HtmlPreviewControllerTest::increasesZoomFactorOnZoomIn()
{
    qreal previousZoomFactor = 1.0;
    webView->setZoomFactor(previousZoomFactor);

    controller->zoomInView();

    QVERIFY(webView->zoomFactor() > previousZoomFactor);
}

void HtmlPreviewControllerTest::decreasesZoomFactorOnZoomOut()
{
    qreal previousZoomFactor = 1.0;
    webView->setZoomFactor(previousZoomFactor);

    controller->zoomOutView();

    QVERIFY(webView->zoomFactor() < previousZoomFactor);
}

void HtmlPreviewControllerTest::resetsZoomFactorOnZoomReset()
{
    qreal previousZoomFactor = 2.0;
    webView->setZoomFactor(previousZoomFactor);

    controller->resetZoomOfView();

    QCOMPARE(webView->zoomFactor(), 1.0);
}

void HtmlPreviewControllerTest::zoomsInOnCtrlPlusKeyPress()
{
    qreal previousZoomFactor = 1.0;
    webView->setZoomFactor(previousZoomFactor);

    QTest::keyClick(webView, Qt::Key_Plus, Qt::ControlModifier);

    QVERIFY(webView->zoomFactor() > previousZoomFactor);
}

void HtmlPreviewControllerTest::zoomsOutOnCtrlMinusKeyPress()
{
    qreal previousZoomFactor = 1.0;
    webView->setZoomFactor(previousZoomFactor);

    QTest::keyClick(webView, Qt::Key_Minus, Qt::ControlModifier);

    QVERIFY(webView->zoomFactor() < previousZoomFactor);
}

void HtmlPreviewControllerTest::resetsZoomOnCtrlZeroKeyPress()
{
    qreal previousZoomFactor = 2.0;
    webView->setZoomFactor(previousZoomFactor);

    QTest::keyClick(webView, Qt::Key_0, Qt::ControlModifier);

    QCOMPARE(webView->zoomFactor(), 1.0);
}

void HtmlPreviewControllerTest::setupsNetworkDiskCache()
{
    QVERIFY(webView->page()->networkAccessManager()->cache() != 0);
}
