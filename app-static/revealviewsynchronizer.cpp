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
#include "revealviewsynchronizer.h"

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QWebFrame>
#include <QWebView>

#include "slidelinemapping.h"


RevealViewSynchronizer::RevealViewSynchronizer(QWebView *webView, QPlainTextEdit *editor) :
    ViewSynchronizer(webView, editor),
    currentSlide(qMakePair(0, 0)),
    slideLineMapping(new SlideLineMapping())
{
    connect(webView, SIGNAL(loadFinished(bool)),
            this, SLOT(registerEvents()));
    connect(webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(restoreSlidePosition()));

    connect(editor, SIGNAL(cursorPositionChanged()),
            this, SLOT(cursorPositionChanged()));
    connect(editor, SIGNAL(textChanged()),
            this, SLOT(textChanged()));

    textChanged();
}

RevealViewSynchronizer::~RevealViewSynchronizer()
{
    delete slideLineMapping;
}

int RevealViewSynchronizer::horizontalSlide() const
{
    return currentSlide.first;
}

int RevealViewSynchronizer::verticalSlide() const
{
    return currentSlide.second;
}

void RevealViewSynchronizer::slideChanged(int horizontal, int vertical)
{
    if (currentSlide.first == horizontal && currentSlide.second == vertical)
        return;

    currentSlide = qMakePair(horizontal, vertical);

    int lineNumber = slideLineMapping->lineForSlide(currentSlide);
    if (lineNumber > 0) {
        gotoLine(lineNumber);
    }
}

void RevealViewSynchronizer::registerEvents()
{
    m_webView->page()->mainFrame()->evaluateJavaScript(
                    "(function(){"
                    "  var mainWinUpdate = false;"
                    "  function feedbackPosition(event) {"
                    "    if (mainWinUpdate) return;"
                    "    synchronizer.slideChanged(event.indexh, event.indexv);"
                    "  }"
                    "  Reveal.addEventListener('ready', function() {"
                    "    Reveal.addEventListener('slidechanged', feedbackPosition);"
                    "  });"
                    "  function gotoSlide(horizontal, vertical) {"
                    "    mainWinUpdate = true;"
                    "    Reveal.slide(horizontal, vertical);"
                    "    mainWinUpdate = false;"
                    "  }"
                    "  synchronizer.gotoSlideRequested.connect(gotoSlide);"
                    "})();");
}

void RevealViewSynchronizer::restoreSlidePosition()
{
    static QString restorePosition =
        "window.location.hash = '/'+synchronizer.horizontalSlide+'/'+synchronizer.verticalSlide;";
    m_webView->page()->mainFrame()->evaluateJavaScript(restorePosition);
}

void RevealViewSynchronizer::cursorPositionChanged()
{
    int lineNumber = m_editor->textCursor().blockNumber() + 1;

    QPair<int, int> slide = slideLineMapping->slideForLine(lineNumber);
    if (slide.first >= 0 && slide.second >= 0) {
        gotoSlide(slide);
    }
}

void RevealViewSynchronizer::textChanged()
{
    QString code = m_editor->toPlainText();
    slideLineMapping->build(code);
}

void RevealViewSynchronizer::gotoLine(int lineNumber)
{
    QTextCursor cursor(m_editor->document()->findBlockByNumber(lineNumber-1));
    m_editor->setTextCursor(cursor);
}

void RevealViewSynchronizer::gotoSlide(QPair<int, int> slide)
{
    if (currentSlide.first == slide.first && currentSlide.second == slide.second)
        return;

    currentSlide = slide;
    emit gotoSlideRequested(slide.first, slide.second);
}
