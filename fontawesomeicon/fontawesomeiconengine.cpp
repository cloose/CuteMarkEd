/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * The names of its contributors may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "fontawesomeiconengine.h"

#include <QFontDatabase>
#include <QPainter>
#include <QPixmapCache>

int FontAwesomeIconEngine::fontId = -1;
QString FontAwesomeIconEngine::fontName;
QHash<QString, QChar> FontAwesomeIconEngine::namedCodepoints;

FontAwesomeIconEngine::FontAwesomeIconEngine() :
    QIconEngine()
{
    loadFont();
}

FontAwesomeIconEngine::FontAwesomeIconEngine(const QString &iconName) :
    QIconEngine()
{
    setIconName(iconName);
}

void FontAwesomeIconEngine::setIconName(const QString &iconName)
{
    this->iconName = iconName;
}

QIconEngine *FontAwesomeIconEngine::clone() const
{
    return new FontAwesomeIconEngine(iconName);
}

void FontAwesomeIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state)
{
    Q_UNUSED(mode)
    Q_UNUSED(state)

    painter->save();

    int pixelSize = qRound(rect.height()*0.625f);
    QFont font(fontName, pixelSize);
    painter->setFont(font);

    QString text = QString(namedCodepoints.value(iconName));
    painter->drawText(rect, Qt::AlignCenter, text);

    painter->restore();
}

QPixmap FontAwesomeIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)
{
    QString key = QString("icons:%1:%2:%3").arg(iconName).arg(size.width()).arg(size.height());

    QPixmap pm(size);
    pm.fill(Qt::transparent);

    if (!QPixmapCache::find(key, pm)) {
        QPainter p(&pm);
        paint(&p, QRect(QPoint(0,0),size), mode, state);
        QPixmapCache::insert(key, pm);
    }

    return pm;
}

void FontAwesomeIconEngine::loadFont()
{
    if (fontId < 0) {
        fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome.ttf");

        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        fontName = fontFamilies.at(0);

        // 0xf000
        namedCodepoints.insert("icon-glass", QChar(0xf000));
        namedCodepoints.insert("icon-music", QChar(0xf001));
        namedCodepoints.insert("icon-search", QChar(0xf002));
        namedCodepoints.insert("icon-envelope-alt", QChar(0xf003));
        namedCodepoints.insert("icon-heart", QChar(0xf004));
        namedCodepoints.insert("icon-star", QChar(0xf005));
        namedCodepoints.insert("icon-star-empty", QChar(0xf006));
        namedCodepoints.insert("icon-user", QChar(0xf007));
        namedCodepoints.insert("icon-film", QChar(0xf008));
        namedCodepoints.insert("icon-th-large", QChar(0xf009));
        namedCodepoints.insert("icon-th", QChar(0xf00a));
        namedCodepoints.insert("icon-th-list", QChar(0xf00b));
        namedCodepoints.insert("icon-ok", QChar(0xf00c));
        namedCodepoints.insert("icon-remove", QChar(0xf00d));
        namedCodepoints.insert("icon-zoom-in", QChar(0xf00e));

        // 0xf010
        namedCodepoints.insert("icon-zoom-out", QChar(0xf010));
        namedCodepoints.insert("icon-off", QChar(0xf011));
        namedCodepoints.insert("icon-signal", QChar(0xf012));
        namedCodepoints.insert("icon-cog", QChar(0xf013));
        namedCodepoints.insert("icon-trash", QChar(0xf014));
        namedCodepoints.insert("icon-home", QChar(0xf015));
        namedCodepoints.insert("icon-file-alt", QChar(0xf016));
        namedCodepoints.insert("icon-time", QChar(0xf017));
        namedCodepoints.insert("icon-road", QChar(0xf018));
        namedCodepoints.insert("icon-download-alt", QChar(0xf019));
        namedCodepoints.insert("icon-download", QChar(0xf01a));
        namedCodepoints.insert("icon-upload", QChar(0xf01b));
        namedCodepoints.insert("icon-inbox", QChar(0xf01c));
        namedCodepoints.insert("icon-play-circle", QChar(0xf01d));
        namedCodepoints.insert("icon-repeat", QChar(0xf01e));

        // 0xf020
        namedCodepoints.insert("icon-refresh", QChar(0xf021));
        namedCodepoints.insert("icon-print", QChar(0xf02f));

        // 0xf030
        namedCodepoints.insert("icon-font", QChar(0xf031));
        namedCodepoints.insert("icon-bold", QChar(0xf032));
        namedCodepoints.insert("icon-italic", QChar(0xf033));
        namedCodepoints.insert("icon-text-height", QChar(0xf034));
        namedCodepoints.insert("icon-text-width", QChar(0xf035));
        namedCodepoints.insert("icon-align-left", QChar(0xf036));
        namedCodepoints.insert("icon-align-center", QChar(0xf037));
        namedCodepoints.insert("icon-align-right", QChar(0xf038));
        namedCodepoints.insert("icon-align-justify", QChar(0xf039));
        namedCodepoints.insert("icon-list", QChar(0xf03a));
        namedCodepoints.insert("icon-indent-left", QChar(0xf03b));
        namedCodepoints.insert("icon-indent-right", QChar(0xf03c));
        namedCodepoints.insert("icon-picture", QChar(0xf03e));

        // 0xf040
        namedCodepoints.insert("icon-pencil", QChar(0xf040));
        namedCodepoints.insert("icon-edit", QChar(0xf044));
        namedCodepoints.insert("icon-share", QChar(0xf045));
        namedCodepoints.insert("icon-check", QChar(0xf046));
        namedCodepoints.insert("icon-move", QChar(0xf047));

        // 0xf050
        namedCodepoints.insert("icon-remove-sign", QChar(0xf057));
        namedCodepoints.insert("icon-ok-sign", QChar(0xf058));
        namedCodepoints.insert("icon-question-sign", QChar(0xf059));
        namedCodepoints.insert("icon-info-sign", QChar(0xf05a));

        // 0xf060
        namedCodepoints.insert("icon-exclamation-sign", QChar(0xf06a));

        // 0xf070
        namedCodepoints.insert("icon-warning-sign", QChar(0xf071));

        // 0xf080
        namedCodepoints.insert("icon-cogs", QChar(0xf085));
        namedCodepoints.insert("icon-external-link", QChar(0xf08e));

        // 0xf0a0
        namedCodepoints.insert("icon-globe", QChar(0xf0ac));
        namedCodepoints.insert("icon-wrench", QChar(0xf0ad));
        namedCodepoints.insert("icon-tasks", QChar(0xf0ae));

        // 0xf0b0
        namedCodepoints.insert("icon-filter", QChar(0xf0b0));
        namedCodepoints.insert("icon-briefcase", QChar(0xf0b1));
        namedCodepoints.insert("icon-fullscreen", QChar(0xf0b2));

        // 0xf0c0
        namedCodepoints.insert("icon-group", QChar(0xf0c0));
        namedCodepoints.insert("icon-link", QChar(0xf0c1));
        namedCodepoints.insert("icon-cloud", QChar(0xf0c2));
        namedCodepoints.insert("icon-cut", QChar(0xf0c4));
        namedCodepoints.insert("icon-copy", QChar(0xf0c5));
        namedCodepoints.insert("icon-paper-clip", QChar(0xf0c6));
        namedCodepoints.insert("icon-save", QChar(0xf0c7));
        namedCodepoints.insert("icon-sign-blank", QChar(0xf0c8));
        namedCodepoints.insert("icon-reorder", QChar(0xf0c9));
        namedCodepoints.insert("icon-list-ul", QChar(0xf0ca));
        namedCodepoints.insert("icon-list-ol", QChar(0xf0cb));
        namedCodepoints.insert("icon-strikethrough", QChar(0xf0cc));
        namedCodepoints.insert("icon-underline", QChar(0xf0cd));
        namedCodepoints.insert("icon-table", QChar(0xf0ce));

        // 0xf0e0
        namedCodepoints.insert("icon-envelope", QChar(0xf0e0));
        namedCodepoints.insert("icon-undo", QChar(0xf0e2));
        namedCodepoints.insert("icon-sitemap", QChar(0xf0e8));
        namedCodepoints.insert("icon-paste", QChar(0xf0ea));

        // 0xf0f0
        namedCodepoints.insert("icon-file-text-alt", QChar(0xf0f6));

        // 0xf100
        namedCodepoints.insert("icon-quote-left", QChar(0xf10d));
        namedCodepoints.insert("icon-quote-right", QChar(0xf10e));

        // 0xf110
        namedCodepoints.insert("icon-keyboard", QChar(0xf11c));

        // 0xf120
        namedCodepoints.insert("icon-terminal", QChar(0xf120));
        namedCodepoints.insert("icon-code", QChar(0xf121));
        namedCodepoints.insert("icon-code-fork", QChar(0xf126));
        namedCodepoints.insert("icon-unlink", QChar(0xf127));
        namedCodepoints.insert("icon-question", QChar(0xf128));
        namedCodepoints.insert("icon-info", QChar(0xf129));
        namedCodepoints.insert("icon-exclamation", QChar(0xf12a));
        namedCodepoints.insert("icon-superscript", QChar(0xf12b));
        namedCodepoints.insert("icon-subscript", QChar(0xf12c));
        namedCodepoints.insert("icon-eraser", QChar(0xf12d));
        namedCodepoints.insert("icon-puzzle-piece", QChar(0xf12e));

        // 0xf130
        namedCodepoints.insert("icon-html5", QChar(0xf13b));
        namedCodepoints.insert("icon-anchor", QChar(0xf13d));

        // 0xf140
        namedCodepoints.insert("icon-level-up", QChar(0xf148));
        namedCodepoints.insert("icon-level-down", QChar(0xf149));

        // 0xf150
        namedCodepoints.insert("icon-file", QChar(0xf15b));
        namedCodepoints.insert("icon-file-text", QChar(0xf15c));
        namedCodepoints.insert("icon-sort-by-alphabet", QChar(0xf15d));
        namedCodepoints.insert("icon-sort-by-alphabet-alt", QChar(0xf15e));

        // 0xf188
        namedCodepoints.insert("icon-bug", QChar(0xf188));
    }
}
