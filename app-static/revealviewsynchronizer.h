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
#ifndef REVEALVIEWSYNCHRONIZER_H
#define REVEALVIEWSYNCHRONIZER_H

#include "viewsynchronizer.h"

#include <QPair>

class SlideLineMapping;


class RevealViewSynchronizer : public ViewSynchronizer
{
    Q_OBJECT
    Q_PROPERTY(int horizontalSlide READ horizontalSlide NOTIFY gotoSlideRequested)
    Q_PROPERTY(int verticalSlide READ verticalSlide NOTIFY gotoSlideRequested)

public:
    RevealViewSynchronizer(QWebView *webView, QPlainTextEdit *editor);
    ~RevealViewSynchronizer();

    int horizontalSlide() const;
    int verticalSlide() const;

signals:
    void gotoSlideRequested(int horizontal, int vertical);

public slots:
    void slideChanged(int horizontal, int vertical);

private slots:
    void registerEvents();
    void restoreSlidePosition();
    void cursorPositionChanged();
    void textChanged();

private:
    void gotoLine(int lineNumber);
    void gotoSlide(QPair<int, int> slide);

private:
    QPair<int, int> currentSlide;
    SlideLineMapping *slideLineMapping;
};

#endif // REVEALVIEWSYNCHRONIZER_H

