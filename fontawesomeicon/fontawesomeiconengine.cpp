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
#include <QPalette>
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

    QPalette::ColorGroup colorGroup = QPalette::Active;
    if (mode == QIcon::Disabled) {
        colorGroup = QPalette::Disabled;
    }
    QPalette palette;
    painter->setPen(palette.color(colorGroup, QPalette::WindowText));

    QString text = QString(namedCodepoints.value(iconName));
    painter->drawText(rect, Qt::AlignCenter, text);

    painter->restore();
}

QPixmap FontAwesomeIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)
{
    QString key = QString("icons:%1:%2:%3:%4").arg(iconName).arg(size.width()).arg(size.height()).arg(mode);

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
        namedCodepoints.insert("fa-glass", QChar(0xf000));
        namedCodepoints.insert("fa-music", QChar(0xf001));
        namedCodepoints.insert("fa-search", QChar(0xf002));
        namedCodepoints.insert("fa-envelope-o", QChar(0xf003));
        namedCodepoints.insert("fa-heart", QChar(0xf004));
        namedCodepoints.insert("fa-star", QChar(0xf005));
        namedCodepoints.insert("fa-star-o", QChar(0xf006));
        namedCodepoints.insert("fa-user", QChar(0xf007));
        namedCodepoints.insert("fa-film", QChar(0xf008));
        namedCodepoints.insert("fa-th-large", QChar(0xf009));
        namedCodepoints.insert("fa-th", QChar(0xf00a));
        namedCodepoints.insert("fa-th-list", QChar(0xf00b));
        namedCodepoints.insert("fa-check", QChar(0xf00c));
        namedCodepoints.insert("fa-times", QChar(0xf00d));
        namedCodepoints.insert("fa-close", QChar(0xf00d)); // alias
        namedCodepoints.insert("fa-remove", QChar(0xf00d)); // alias
        namedCodepoints.insert("fa-search-plus", QChar(0xf00e));

        // 0xf010
        namedCodepoints.insert("fa-search-minus", QChar(0xf010));
        namedCodepoints.insert("fa-power-off", QChar(0xf011));
        namedCodepoints.insert("fa-signal", QChar(0xf012));
        namedCodepoints.insert("fa-cog", QChar(0xf013));
        namedCodepoints.insert("fa-gear", QChar(0xf013)); // alias
        namedCodepoints.insert("fa-trash-o", QChar(0xf014));
        namedCodepoints.insert("fa-home", QChar(0xf015));
        namedCodepoints.insert("fa-file-o", QChar(0xf016));
        namedCodepoints.insert("fa-clock-o", QChar(0xf017));
        namedCodepoints.insert("fa-road", QChar(0xf018));
        namedCodepoints.insert("fa-download", QChar(0xf019));
        namedCodepoints.insert("fa-arrow-circle-o-down", QChar(0xf01a));
        namedCodepoints.insert("fa-arrow-circle-o-up", QChar(0xf01b));
        namedCodepoints.insert("fa-inbox", QChar(0xf01c));
        namedCodepoints.insert("fa-play-circle-o", QChar(0xf01d));
        namedCodepoints.insert("fa-repeat", QChar(0xf01e));
        namedCodepoints.insert("fa-rotate-right", QChar(0xf01e)); // alias

        // 0xf021
        namedCodepoints.insert("fa-refresh", QChar(0xf021));
        namedCodepoints.insert("fa-list-alt", QChar(0xf022));
        namedCodepoints.insert("fa-lock", QChar(0xf023));
        namedCodepoints.insert("fa-flag", QChar(0xf024));
        namedCodepoints.insert("fa-headphones", QChar(0xf025));
        namedCodepoints.insert("fa-volume-off", QChar(0xf026));
        namedCodepoints.insert("fa-volume-down", QChar(0xf027));
        namedCodepoints.insert("fa-volume-up", QChar(0xf028));
        namedCodepoints.insert("fa-qrcode", QChar(0xf029));
        namedCodepoints.insert("fa-barcode", QChar(0xf02a));
        namedCodepoints.insert("fa-tag", QChar(0xf02b));
        namedCodepoints.insert("fa-tags", QChar(0xf02c));
        namedCodepoints.insert("fa-book", QChar(0xf02d));
        namedCodepoints.insert("fa-bookmark", QChar(0xf02e));
        namedCodepoints.insert("fa-print", QChar(0xf02f));

        // 0xf030
        namedCodepoints.insert("fa-camera", QChar(0xf030));
        namedCodepoints.insert("fa-font", QChar(0xf031));
        namedCodepoints.insert("fa-bold", QChar(0xf032));
        namedCodepoints.insert("fa-italic", QChar(0xf033));
        namedCodepoints.insert("fa-text-height", QChar(0xf034));
        namedCodepoints.insert("fa-text-width", QChar(0xf035));
        namedCodepoints.insert("fa-align-left", QChar(0xf036));
        namedCodepoints.insert("fa-align-center", QChar(0xf037));
        namedCodepoints.insert("fa-align-right", QChar(0xf038));
        namedCodepoints.insert("fa-align-justify", QChar(0xf039));
        namedCodepoints.insert("fa-list", QChar(0xf03a));
        namedCodepoints.insert("fa-outdent", QChar(0xf03b));
        namedCodepoints.insert("fa-dedent", QChar(0xf03b)); // alias
        namedCodepoints.insert("fa-indent", QChar(0xf03c));
        namedCodepoints.insert("fa-video-camera", QChar(0xf03d));
        namedCodepoints.insert("fa-picture-o", QChar(0xf03e));
        namedCodepoints.insert("fa-photo", QChar(0xf03e)); // alias
        namedCodepoints.insert("fa-image", QChar(0xf03e)); // alias

        // 0xf040
        namedCodepoints.insert("fa-pencil", QChar(0xf040));
        namedCodepoints.insert("fa-map-marker", QChar(0xf041));
        namedCodepoints.insert("fa-adjust", QChar(0xf042));
        namedCodepoints.insert("fa-tint", QChar(0xf043));
        namedCodepoints.insert("fa-pencil-square-o", QChar(0xf044));
        namedCodepoints.insert("fa-edit", QChar(0xf044)); // alias
        namedCodepoints.insert("fa-share-square-o", QChar(0xf045));
        namedCodepoints.insert("fa-check-square-o", QChar(0xf046));
        namedCodepoints.insert("fa-arrows", QChar(0xf047));
        namedCodepoints.insert("fa-step-backward", QChar(0xf048));
        namedCodepoints.insert("fa-fast-backward", QChar(0xf049));
        namedCodepoints.insert("fa-backward", QChar(0xf04a));
        namedCodepoints.insert("fa-play", QChar(0xf04b));
        namedCodepoints.insert("fa-pause", QChar(0xf04c));
        namedCodepoints.insert("fa-stop", QChar(0xf04d));
        namedCodepoints.insert("fa-forward", QChar(0xf04e));

        // 0xf050
        namedCodepoints.insert("fa-fast-forward", QChar(0xf050));
        namedCodepoints.insert("fa-step-forward", QChar(0xf051));
        namedCodepoints.insert("fa-eject", QChar(0xf052));
        namedCodepoints.insert("fa-chevron-left", QChar(0xf053));
        namedCodepoints.insert("fa-chevron-right", QChar(0xf054));
        namedCodepoints.insert("fa-plus-circle", QChar(0xf055));
        namedCodepoints.insert("fa-minus-circle", QChar(0xf056));
        namedCodepoints.insert("fa-times-circle", QChar(0xf057));
        namedCodepoints.insert("fa-check-circle", QChar(0xf058));
        namedCodepoints.insert("fa-question-circle", QChar(0xf059));
        namedCodepoints.insert("fa-info-circle", QChar(0xf05a));
        namedCodepoints.insert("fa-crosshairs", QChar(0xf05b));
        namedCodepoints.insert("fa-times-circle-o", QChar(0xf05c));
        namedCodepoints.insert("fa-check-circle-o", QChar(0xf05d));
        namedCodepoints.insert("fa-ban", QChar(0xf05e));

        // 0xf060
        namedCodepoints.insert("fa-arrow-left", QChar(0xf060));
        namedCodepoints.insert("fa-arrow-right", QChar(0xf061));
        namedCodepoints.insert("fa-arrow-up", QChar(0xf062));
        namedCodepoints.insert("fa-arrow-down", QChar(0xf063));
        namedCodepoints.insert("fa-share", QChar(0xf064));
        namedCodepoints.insert("fa-mail-forward", QChar(0xf064)); // alias
        namedCodepoints.insert("fa-expand", QChar(0xf065));
        namedCodepoints.insert("fa-compress", QChar(0xf066));
        namedCodepoints.insert("fa-plus", QChar(0xf067));
        namedCodepoints.insert("fa-minus", QChar(0xf068));
        namedCodepoints.insert("fa-asterisk", QChar(0xf069));
        namedCodepoints.insert("fa-exclamation-circle", QChar(0xf06a));
        namedCodepoints.insert("fa-gift", QChar(0xf06b));
        namedCodepoints.insert("fa-leaf", QChar(0xf06c));
        namedCodepoints.insert("fa-fire", QChar(0xf06d));
        namedCodepoints.insert("fa-eye", QChar(0xf06e));

        // 0xf070
        namedCodepoints.insert("fa-eye-slash", QChar(0xf070));
        namedCodepoints.insert("fa-exclamation-triangle", QChar(0xf071));
        namedCodepoints.insert("fa-warning", QChar(0xf071)); // alias
        namedCodepoints.insert("fa-plane", QChar(0xf072));
        namedCodepoints.insert("fa-calendar", QChar(0xf073));
        namedCodepoints.insert("fa-random", QChar(0xf074));
        namedCodepoints.insert("fa-comment", QChar(0xf075));
        namedCodepoints.insert("fa-magnet", QChar(0xf076));
        namedCodepoints.insert("fa-chevron-up", QChar(0xf077));
        namedCodepoints.insert("fa-chevron-down", QChar(0xf078));
        namedCodepoints.insert("fa-retweet", QChar(0xf079));
        namedCodepoints.insert("fa-shopping-cart", QChar(0xf07a));
        namedCodepoints.insert("fa-folder", QChar(0xf07b));
        namedCodepoints.insert("fa-folder-open", QChar(0xf07c));
        namedCodepoints.insert("fa-arrows-v", QChar(0xf07d));
        namedCodepoints.insert("fa-arrows-h", QChar(0xf07e));

        // 0xf080
        namedCodepoints.insert("fa-bar-chart", QChar(0xf080));
        namedCodepoints.insert("fa-bar-chart-o", QChar(0xf080)); // alias
        namedCodepoints.insert("fa-twitter-square", QChar(0xf081));
        namedCodepoints.insert("fa-facebook-square", QChar(0xf082));
        namedCodepoints.insert("fa-camera-retro", QChar(0xf083));
        namedCodepoints.insert("fa-key", QChar(0xf084));
        namedCodepoints.insert("fa-cogs", QChar(0xf085));
        namedCodepoints.insert("fa-gears", QChar(0xf085)); // alias
        namedCodepoints.insert("fa-comments", QChar(0xf086));
        namedCodepoints.insert("fa-thumbs-o-up", QChar(0xf087));
        namedCodepoints.insert("fa-thumbs-o-down", QChar(0xf088));
        namedCodepoints.insert("fa-star-half", QChar(0xf089));
        namedCodepoints.insert("fa-heart-o", QChar(0xf08a));
        namedCodepoints.insert("fa-sign-out", QChar(0xf08b));
        namedCodepoints.insert("fa-linkedin-square", QChar(0xf08c));
        namedCodepoints.insert("fa-thumb-tack", QChar(0xf08d));
        namedCodepoints.insert("fa-external-link", QChar(0xf08e));

        // 0xf090
        namedCodepoints.insert("fa-sign-in", QChar(0xf090));
        namedCodepoints.insert("fa-trophy", QChar(0xf091));
        namedCodepoints.insert("fa-github-square", QChar(0xf092));
        namedCodepoints.insert("fa-upload", QChar(0xf093));
        namedCodepoints.insert("fa-lemon-o", QChar(0xf094));
        namedCodepoints.insert("fa-phone", QChar(0xf095));
        namedCodepoints.insert("fa-square-o", QChar(0xf096));
        namedCodepoints.insert("fa-bookmark-o", QChar(0xf097));
        namedCodepoints.insert("fa-phone-square", QChar(0xf098));
        namedCodepoints.insert("fa-twitter", QChar(0xf099));
        namedCodepoints.insert("fa-facebook", QChar(0xf09a));
        namedCodepoints.insert("fa-github", QChar(0xf09b));
        namedCodepoints.insert("fa-unlock", QChar(0xf09c));
        namedCodepoints.insert("fa-credit-card", QChar(0xf09d));
        namedCodepoints.insert("fa-rss", QChar(0xf09e));

        // 0xf0a0
        namedCodepoints.insert("fa-hdd-o", QChar(0xf0a0));
        namedCodepoints.insert("fa-bullhorn", QChar(0xf0a1));
        namedCodepoints.insert("fa-bell-o", QChar(0xf0a2));
        namedCodepoints.insert("fa-certificate", QChar(0xf0a3));
        namedCodepoints.insert("fa-hand-o-right", QChar(0xf0a4));
        namedCodepoints.insert("fa-hand-o-left", QChar(0xf0a5));
        namedCodepoints.insert("fa-hand-o-up", QChar(0xf0a6));
        namedCodepoints.insert("fa-hand-o-down", QChar(0xf0a7));
        namedCodepoints.insert("fa-arrow-circle-left", QChar(0xf0a8));
        namedCodepoints.insert("fa-arrow-circle-right", QChar(0xf0a9));
        namedCodepoints.insert("fa-arrow-circle-up", QChar(0xf0aa));
        namedCodepoints.insert("fa-arrow-circle-down", QChar(0xf0ab));
        namedCodepoints.insert("fa-globe", QChar(0xf0ac));
        namedCodepoints.insert("fa-wrench", QChar(0xf0ad));
        namedCodepoints.insert("fa-tasks", QChar(0xf0ae));

        // 0xf0b0
        namedCodepoints.insert("fa-filter", QChar(0xf0b0));
        namedCodepoints.insert("fa-briefcase", QChar(0xf0b1));
        namedCodepoints.insert("fa-arrows-alt", QChar(0xf0b2));

        // 0xf0c0
        namedCodepoints.insert("fa-users", QChar(0xf0c0));
        namedCodepoints.insert("fa-group", QChar(0xf0c0)); // alias
        namedCodepoints.insert("fa-link", QChar(0xf0c1));
        namedCodepoints.insert("fa-chain", QChar(0xf0c1)); // alias
        namedCodepoints.insert("fa-cloud", QChar(0xf0c2));
        namedCodepoints.insert("fa-flask", QChar(0xf0c3));
        namedCodepoints.insert("fa-scissors", QChar(0xf0c4));
        namedCodepoints.insert("fa-cut", QChar(0xf0c4)); // alias
        namedCodepoints.insert("fa-files-o", QChar(0xf0c5));
        namedCodepoints.insert("fa-copy", QChar(0xf0c5)); // alias
        namedCodepoints.insert("fa-paperclip", QChar(0xf0c6));
        namedCodepoints.insert("fa-floppy-o", QChar(0xf0c7));
        namedCodepoints.insert("fa-save", QChar(0xf0c7)); // alias
        namedCodepoints.insert("fa-square", QChar(0xf0c8));
        namedCodepoints.insert("fa-bars", QChar(0xf0c9));
        namedCodepoints.insert("fa-navicon", QChar(0xf0c9)); // alias
        namedCodepoints.insert("fa-reorder", QChar(0xf0c9)); // alias
        namedCodepoints.insert("fa-list-ul", QChar(0xf0ca));
        namedCodepoints.insert("fa-list-ol", QChar(0xf0cb));
        namedCodepoints.insert("fa-strikethrough", QChar(0xf0cc));
        namedCodepoints.insert("fa-underline", QChar(0xf0cd));
        namedCodepoints.insert("fa-table", QChar(0xf0ce));

        // 0xf0d0
        namedCodepoints.insert("fa-magic", QChar(0xf0d0));
        namedCodepoints.insert("fa-truck", QChar(0xf0d1));
        namedCodepoints.insert("fa-pinterest", QChar(0xf0d2));
        namedCodepoints.insert("fa-pinterest-square", QChar(0xf0d3));
        namedCodepoints.insert("fa-google-plus-square", QChar(0xf0d4));
        namedCodepoints.insert("fa-google-plus", QChar(0xf0d5));
        namedCodepoints.insert("fa-money", QChar(0xf0d6));
        namedCodepoints.insert("fa-caret-down", QChar(0xf0d7));
        namedCodepoints.insert("fa-caret-up", QChar(0xf0d8));
        namedCodepoints.insert("fa-caret-left", QChar(0xf0d9));
        namedCodepoints.insert("fa-caret-right", QChar(0xf0da));
        namedCodepoints.insert("fa-columns", QChar(0xf0db));
        namedCodepoints.insert("fa-sort", QChar(0xf0dc));
        namedCodepoints.insert("fa-unsorted", QChar(0xf0dc)); // alias
        namedCodepoints.insert("fa-sort-asc", QChar(0xf0dd));
        namedCodepoints.insert("fa-sort-down", QChar(0xf0dd)); // alias
        namedCodepoints.insert("fa-sort-desc", QChar(0xf0de));
        namedCodepoints.insert("fa-sort-up", QChar(0xf0de)); // alias

        // 0xf0e0
        namedCodepoints.insert("fa-envelope", QChar(0xf0e0));
        namedCodepoints.insert("fa-linkedin", QChar(0xf0e1));
        namedCodepoints.insert("fa-undo", QChar(0xf0e2));
        namedCodepoints.insert("fa-rotate-left", QChar(0xf0e2)); // alias
        namedCodepoints.insert("fa-gavel", QChar(0xf0e3));
        namedCodepoints.insert("fa-legal", QChar(0xf0e3)); // alias
        namedCodepoints.insert("fa-tachometer", QChar(0xf0e4));
        namedCodepoints.insert("fa-dashboard", QChar(0xf0e4)); // alias
        namedCodepoints.insert("fa-comment-o", QChar(0xf0e5));
        namedCodepoints.insert("fa-comments-o", QChar(0xf0e6));
        namedCodepoints.insert("fa-bolt", QChar(0xf0e7));
        namedCodepoints.insert("fa-flash", QChar(0xf0e7)); // alias
        namedCodepoints.insert("fa-sitemap", QChar(0xf0e8));
        namedCodepoints.insert("fa-umbrella", QChar(0xf0e9));
        namedCodepoints.insert("fa-clipboard", QChar(0xf0ea));
        namedCodepoints.insert("fa-paste", QChar(0xf0ea)); // alias
        namedCodepoints.insert("fa-lightbulb-o", QChar(0xf0eb));
        namedCodepoints.insert("fa-exchange", QChar(0xf0ec));
        namedCodepoints.insert("fa-cloud-download", QChar(0xf0ed));
        namedCodepoints.insert("fa-cloud-upload", QChar(0xf0ee));

        // 0xf0f0
        namedCodepoints.insert("fa-user-md", QChar(0xf0f0));
        namedCodepoints.insert("fa-stethoscope", QChar(0xf0f1));
        namedCodepoints.insert("fa-suitcase", QChar(0xf0f2));
        namedCodepoints.insert("fa-bell", QChar(0xf0f3));
        namedCodepoints.insert("fa-coffee", QChar(0xf0f4));
        namedCodepoints.insert("fa-cutlery", QChar(0xf0f5));
        namedCodepoints.insert("fa-file-text-o", QChar(0xf0f6));
        namedCodepoints.insert("fa-building-o", QChar(0xf0f7));
        namedCodepoints.insert("fa-hospital-o", QChar(0xf0f8));
        namedCodepoints.insert("fa-ambulance", QChar(0xf0f9));
        namedCodepoints.insert("fa-medkit", QChar(0xf0fa));
        namedCodepoints.insert("fa-fighter-jet", QChar(0xf0fb));
        namedCodepoints.insert("fa-beer", QChar(0xf0fc));
        namedCodepoints.insert("fa-h-square", QChar(0xf0fd));
        namedCodepoints.insert("fa-plus-square", QChar(0xf0fe));

        // 0xf100
        namedCodepoints.insert("fa-angle-double-left", QChar(0xf100));
        namedCodepoints.insert("fa-angle-double-right", QChar(0xf101));
        namedCodepoints.insert("fa-angle-double-up", QChar(0xf102));
        namedCodepoints.insert("fa-angle-double-down", QChar(0xf103));
        namedCodepoints.insert("fa-angle-left", QChar(0xf104));
        namedCodepoints.insert("fa-angle-right", QChar(0xf105));
        namedCodepoints.insert("fa-angle-up", QChar(0xf106));
        namedCodepoints.insert("fa-angle-down", QChar(0xf107));
        namedCodepoints.insert("fa-desktop", QChar(0xf108));
        namedCodepoints.insert("fa-laptop", QChar(0xf109));
        namedCodepoints.insert("fa-tablet", QChar(0xf10a));
        namedCodepoints.insert("fa-mobile", QChar(0xf10b));
        namedCodepoints.insert("fa-mobile-phone", QChar(0xf10b)); // alias
        namedCodepoints.insert("fa-circle-o", QChar(0xf10c));
        namedCodepoints.insert("fa-quote-left", QChar(0xf10d));
        namedCodepoints.insert("fa-quote-right", QChar(0xf10e));

        // 0xf110
        namedCodepoints.insert("fa-spinner", QChar(0xf110));
        namedCodepoints.insert("fa-circle", QChar(0xf111));
        namedCodepoints.insert("fa-reply", QChar(0xf112));
        namedCodepoints.insert("fa-mail-reply", QChar(0xf112)); // alias
        namedCodepoints.insert("fa-github-alt", QChar(0xf113));
        namedCodepoints.insert("fa-folder-o", QChar(0xf114));
        namedCodepoints.insert("fa-folder-open-o", QChar(0xf115));
        namedCodepoints.insert("fa-smile-o", QChar(0xf118));
        namedCodepoints.insert("fa-frown-o", QChar(0xf119));
        namedCodepoints.insert("fa-meh-o", QChar(0xf11a));
        namedCodepoints.insert("fa-gamepad", QChar(0xf11b));
        namedCodepoints.insert("fa-keyboard-o", QChar(0xf11c));
        namedCodepoints.insert("fa-flag-o", QChar(0xf11d));
        namedCodepoints.insert("fa-flag-checkered", QChar(0xf11e));

        // 0xf120
        namedCodepoints.insert("fa-terminal", QChar(0xf120));
        namedCodepoints.insert("fa-code", QChar(0xf121));
        namedCodepoints.insert("fa-reply-all", QChar(0xf122));
        namedCodepoints.insert("fa-mail-reply-all", QChar(0xf122)); // duplicate
        namedCodepoints.insert("fa-star-half-o", QChar(0xf123));
        namedCodepoints.insert("fa-star-half-empty", QChar(0xf123)); // alias
        namedCodepoints.insert("fa-star-half-full", QChar(0xf123)); // alias
        namedCodepoints.insert("fa-location-arrow", QChar(0xf124));
        namedCodepoints.insert("fa-crop", QChar(0xf125));
        namedCodepoints.insert("fa-code-fork", QChar(0xf126));
        namedCodepoints.insert("fa-chain-broken", QChar(0xf127));
        namedCodepoints.insert("fa-unlink", QChar(0xf127)); // alias
        namedCodepoints.insert("fa-question", QChar(0xf128));
        namedCodepoints.insert("fa-info", QChar(0xf129));
        namedCodepoints.insert("fa-exclamation", QChar(0xf12a));
        namedCodepoints.insert("fa-superscript", QChar(0xf12b));
        namedCodepoints.insert("fa-subscript", QChar(0xf12c));
        namedCodepoints.insert("fa-eraser", QChar(0xf12d));
        namedCodepoints.insert("fa-puzzle-piece", QChar(0xf12e));

        // 0xf130
        namedCodepoints.insert("fa-microphone", QChar(0xf130));
        namedCodepoints.insert("fa-microphone-slash", QChar(0xf131));
        namedCodepoints.insert("fa-shield", QChar(0xf132));
        namedCodepoints.insert("fa-calendar-o", QChar(0xf133));
        namedCodepoints.insert("fa-fire-extinguisher", QChar(0xf134));
        namedCodepoints.insert("fa-rocket", QChar(0xf135));
        namedCodepoints.insert("fa-maxcdn", QChar(0xf136));
        namedCodepoints.insert("fa-chevron-circle-left", QChar(0xf137));
        namedCodepoints.insert("fa-chevron-circle-right", QChar(0xf138));
        namedCodepoints.insert("fa-chevron-circle-up", QChar(0xf139));
        namedCodepoints.insert("fa-chevron-circle-down", QChar(0xf13a));
        namedCodepoints.insert("fa-html5", QChar(0xf13b));
        namedCodepoints.insert("fa-css3", QChar(0xf13c));
        namedCodepoints.insert("fa-anchor", QChar(0xf13d));
        namedCodepoints.insert("fa-unlock-alt", QChar(0xf13e));

        // 0xf140
        namedCodepoints.insert("fa-bullseye", QChar(0xf140));
        namedCodepoints.insert("fa-ellipsis-h", QChar(0xf141));
        namedCodepoints.insert("fa-ellipsis-v", QChar(0xf142));
        namedCodepoints.insert("fa-rss-square", QChar(0xf143));
        namedCodepoints.insert("fa-play-circle", QChar(0xf144));
        namedCodepoints.insert("fa-ticket", QChar(0xf145));
        namedCodepoints.insert("fa-minus-square", QChar(0xf146));
        namedCodepoints.insert("fa-minus-square-o", QChar(0xf147));
        namedCodepoints.insert("fa-level-up", QChar(0xf148));
        namedCodepoints.insert("fa-level-down", QChar(0xf149));
        namedCodepoints.insert("fa-check-square", QChar(0xf14a));
        namedCodepoints.insert("fa-pencil-square", QChar(0xf14b));
        namedCodepoints.insert("fa-external-link-square", QChar(0xf14c));
        namedCodepoints.insert("fa-share-square", QChar(0xf14d));
        namedCodepoints.insert("fa-compass", QChar(0xf14e));

        // 0xf150
        namedCodepoints.insert("fa-caret-square-o-down", QChar(0xf150));
        namedCodepoints.insert("fa-toggle-down", QChar(0xf150)); // alias
        namedCodepoints.insert("fa-caret-square-o-up", QChar(0xf151));
        namedCodepoints.insert("fa-toggle-up", QChar(0xf151)); // alias
        namedCodepoints.insert("fa-caret-square-o-right", QChar(0xf152));
        namedCodepoints.insert("fa-toggle-right", QChar(0xf152)); // alias
        namedCodepoints.insert("fa-eur", QChar(0xf153));
        namedCodepoints.insert("fa-euro", QChar(0xf153)); // alias
        namedCodepoints.insert("fa-gbp", QChar(0xf154));
        namedCodepoints.insert("fa-usd", QChar(0xf155));
        namedCodepoints.insert("fa-dollar", QChar(0xf155)); // alias
        namedCodepoints.insert("fa-inr", QChar(0xf156));
        namedCodepoints.insert("fa-rupee", QChar(0xf156)); // alias
        namedCodepoints.insert("fa-jpy", QChar(0xf157));
        namedCodepoints.insert("fa-cny", QChar(0xf157)); // alias
        namedCodepoints.insert("fa-rmb", QChar(0xf157)); // alias
        namedCodepoints.insert("fa-yen", QChar(0xf157)); // alias
        namedCodepoints.insert("fa-rub", QChar(0xf158));
        namedCodepoints.insert("fa-ruble", QChar(0xf158)); // alias
        namedCodepoints.insert("fa-rouble", QChar(0xf158)); // alias
        namedCodepoints.insert("fa-krw", QChar(0xf159));
        namedCodepoints.insert("fa-won", QChar(0xf159)); // alias
        namedCodepoints.insert("fa-btc", QChar(0xf15a));
        namedCodepoints.insert("fa-bitcoin", QChar(0xf15a)); // alias
        namedCodepoints.insert("fa-file", QChar(0xf15b));
        namedCodepoints.insert("fa-file-text", QChar(0xf15c));
        namedCodepoints.insert("fa-sort-alpha-asc", QChar(0xf15d));
        namedCodepoints.insert("fa-sort-alpha-desc", QChar(0xf15e));

        // 0xf160
        namedCodepoints.insert("fa-sort-amount-asc", QChar(0xf160));
        namedCodepoints.insert("fa-sort-amount-desc", QChar(0xf161));
        namedCodepoints.insert("fa-sort-numeric-asc", QChar(0xf162));
        namedCodepoints.insert("fa-sort-numeric-desc", QChar(0xf163));
        namedCodepoints.insert("fa-thumbs-up", QChar(0xf164));
        namedCodepoints.insert("fa-thumbs-down", QChar(0xf165));
        namedCodepoints.insert("fa-youtube-square", QChar(0xf166));
        namedCodepoints.insert("fa-youtube", QChar(0xf167));
        namedCodepoints.insert("fa-xing", QChar(0xf168));
        namedCodepoints.insert("fa-xing-square", QChar(0xf169));
        namedCodepoints.insert("fa-youtube-play", QChar(0xf16a));
        namedCodepoints.insert("fa-dropbox", QChar(0xf16b));
        namedCodepoints.insert("fa-stack-overflow", QChar(0xf16c));
        namedCodepoints.insert("fa-instagram", QChar(0xf16d));
        namedCodepoints.insert("fa-flickr", QChar(0xf16e));

        // 0xf170
        namedCodepoints.insert("fa-adn", QChar(0xf170));
        namedCodepoints.insert("fa-bitbucket", QChar(0xf171));
        namedCodepoints.insert("fa-bitbucket-square", QChar(0xf172));
        namedCodepoints.insert("fa-tumblr", QChar(0xf173));
        namedCodepoints.insert("fa-tumblr-square", QChar(0xf174));
        namedCodepoints.insert("fa-long-arrow-down", QChar(0xf175));
        namedCodepoints.insert("fa-long-arrow-up", QChar(0xf176));
        namedCodepoints.insert("fa-long-arrow-left", QChar(0xf177));
        namedCodepoints.insert("fa-long-arrow-right", QChar(0xf178));
        namedCodepoints.insert("fa-apple", QChar(0xf179));
        namedCodepoints.insert("fa-windows", QChar(0xf17a));
        namedCodepoints.insert("fa-android", QChar(0xf17b));
        namedCodepoints.insert("fa-linux", QChar(0xf17c));
        namedCodepoints.insert("fa-dribbble", QChar(0xf17d));
        namedCodepoints.insert("fa-skype", QChar(0xf17e));

        // 0xf180
        namedCodepoints.insert("fa-foursquare", QChar(0xf180));
        namedCodepoints.insert("fa-trello", QChar(0xf181));
        namedCodepoints.insert("fa-female", QChar(0xf182));
        namedCodepoints.insert("fa-male", QChar(0xf183));
        namedCodepoints.insert("fa-gittip", QChar(0xf184));
        namedCodepoints.insert("fa-sun-o", QChar(0xf185));
        namedCodepoints.insert("fa-moon-o", QChar(0xf186));
        namedCodepoints.insert("fa-archive", QChar(0xf187));
        namedCodepoints.insert("fa-bug", QChar(0xf188));
        namedCodepoints.insert("fa-vk", QChar(0xf189));
        namedCodepoints.insert("fa-weibo", QChar(0xf18a));
        namedCodepoints.insert("fa-renren", QChar(0xf18b));
        namedCodepoints.insert("fa-pagelines", QChar(0xf18c));
        namedCodepoints.insert("fa-stack-exchange", QChar(0xf18d));
        namedCodepoints.insert("fa-arrow-circle-o-right", QChar(0xf18e));

        // 0xf190
        namedCodepoints.insert("fa-arrow-circle-o-left", QChar(0xf190));
        namedCodepoints.insert("fa-caret-square-o-left", QChar(0xf191));
        namedCodepoints.insert("fa-toggle-left", QChar(0xf191)); // alias
        namedCodepoints.insert("fa-dot-circle-o", QChar(0xf192));
        namedCodepoints.insert("fa-wheelchair", QChar(0xf193));
        namedCodepoints.insert("fa-vimeo-square", QChar(0xf194));
        namedCodepoints.insert("fa-try", QChar(0xf195));
        namedCodepoints.insert("fa-turkish-lira", QChar(0xf195)); // alias
        namedCodepoints.insert("fa-plus-square-o", QChar(0xf196));
        namedCodepoints.insert("fa-space-shuttle", QChar(0xf197));
        namedCodepoints.insert("fa-slack", QChar(0xf198));
        namedCodepoints.insert("fa-envelope-square", QChar(0xf199));
        namedCodepoints.insert("fa-wordpress", QChar(0xf19a));
        namedCodepoints.insert("fa-openid", QChar(0xf19b));
        namedCodepoints.insert("fa-university", QChar(0xf19c));
        namedCodepoints.insert("fa-bank", QChar(0xf19c)); // alias
        namedCodepoints.insert("fa-institution", QChar(0xf19c)); // alias
        namedCodepoints.insert("fa-graduation-cap", QChar(0xf19d));
        namedCodepoints.insert("fa-mortar-board", QChar(0xf19d)); // alias
        namedCodepoints.insert("fa-yahoo", QChar(0xf19e));

        // 0xf1a0
        namedCodepoints.insert("fa-google", QChar(0xf1a0));
        namedCodepoints.insert("fa-reddit", QChar(0xf1a1));
        namedCodepoints.insert("fa-reddit-square", QChar(0xf1a2));
        namedCodepoints.insert("fa-stumbleupon-circle", QChar(0xf1a3));
        namedCodepoints.insert("fa-stumbleupon", QChar(0xf1a4));
        namedCodepoints.insert("fa-delicious", QChar(0xf1a5));
        namedCodepoints.insert("fa-digg", QChar(0xf1a6));
        namedCodepoints.insert("fa-pied-piper", QChar(0xf1a7));
        namedCodepoints.insert("fa-pied-piper-alt", QChar(0xf1a8));
        namedCodepoints.insert("fa-drupal", QChar(0xf1a9));
        namedCodepoints.insert("fa-joomla", QChar(0xf1aa));
        namedCodepoints.insert("fa-language", QChar(0xf1ab));
        namedCodepoints.insert("fa-fax", QChar(0xf1ac));
        namedCodepoints.insert("fa-building", QChar(0xf1ad));
        namedCodepoints.insert("fa-child", QChar(0xf1ae));

        // 0xf1b0
        namedCodepoints.insert("fa-paw", QChar(0xf1b0));
        namedCodepoints.insert("fa-spoon", QChar(0xf1b1));
        namedCodepoints.insert("fa-cube", QChar(0xf1b2));
        namedCodepoints.insert("fa-cubes", QChar(0xf1b3));
        namedCodepoints.insert("fa-behance", QChar(0xf1b4));
        namedCodepoints.insert("fa-behance-square", QChar(0xf1b5));
        namedCodepoints.insert("fa-steam", QChar(0xf1b6));
        namedCodepoints.insert("fa-steam-square", QChar(0xf1b7));
        namedCodepoints.insert("fa-recycle", QChar(0xf1b8));
        namedCodepoints.insert("fa-car", QChar(0xf1b9));
        namedCodepoints.insert("fa-automobile", QChar(0xf1b9)); // alias
        namedCodepoints.insert("fa-cab", QChar(0xf1ba)); // alias
        namedCodepoints.insert("fa-taxi", QChar(0xf1ba));
        namedCodepoints.insert("fa-tree", QChar(0xf1bb));
        namedCodepoints.insert("fa-spotify", QChar(0xf1bc));
        namedCodepoints.insert("fa-deviantart", QChar(0xf1bd));
        namedCodepoints.insert("fa-soundcloud", QChar(0xf1be));

        // 0xf1c0
        namedCodepoints.insert("fa-database", QChar(0xf1c0));
        namedCodepoints.insert("fa-file-pdf-o", QChar(0xf1c1));
        namedCodepoints.insert("fa-file-word-o", QChar(0xf1c2));
        namedCodepoints.insert("fa-file-excel-o", QChar(0xf1c3));
        namedCodepoints.insert("fa-file-powerpoint-o", QChar(0xf1c4));
        namedCodepoints.insert("fa-file-image-o", QChar(0xf1c5));
        namedCodepoints.insert("fa-file-photo-o", QChar(0xf1c5)); // alias
        namedCodepoints.insert("fa-file-picture-o", QChar(0xf1c5)); // alias
        namedCodepoints.insert("fa-file-archive-o", QChar(0xf1c6));
        namedCodepoints.insert("fa-file-zip-o", QChar(0xf1c6)); // alias
        namedCodepoints.insert("fa-file-audio-o", QChar(0xf1c7));
        namedCodepoints.insert("fa-file-sound-o", QChar(0xf1c7)); // alias
        namedCodepoints.insert("fa-file-video-o", QChar(0xf1c8));
        namedCodepoints.insert("fa-file-movie-o", QChar(0xf1c8)); // alias
        namedCodepoints.insert("fa-file-code-o", QChar(0xf1c9));
        namedCodepoints.insert("fa-vine", QChar(0xf1ca));
        namedCodepoints.insert("fa-codepen", QChar(0xf1cb));
        namedCodepoints.insert("fa-jsfiddle", QChar(0xf1cc));
        namedCodepoints.insert("fa-life-bouy", QChar(0xf1cd)); // alias
        namedCodepoints.insert("fa-life-buoy", QChar(0xf1cd)); // alias
        namedCodepoints.insert("fa-life-ring", QChar(0xf1cd));
        namedCodepoints.insert("fa-life-saver", QChar(0xf1cd)); // alias
        namedCodepoints.insert("fa-support", QChar(0xf1cd)); // alias
        namedCodepoints.insert("fa-circle-o-notch", QChar(0xf1ce));

        // 0xf1d0
        namedCodepoints.insert("fa-rebel", QChar(0xf1d0));
        namedCodepoints.insert("fa-ra", QChar(0xf1d0)); // alias
        namedCodepoints.insert("fa-empire", QChar(0xf1d1));
        namedCodepoints.insert("fa-ge", QChar(0xf1d1)); // alias
        namedCodepoints.insert("fa-git-square", QChar(0xf1d2));
        namedCodepoints.insert("fa-git", QChar(0xf1d3));
        namedCodepoints.insert("fa-hacker-news", QChar(0xf1d4));
        namedCodepoints.insert("fa-tencent-weibo", QChar(0xf1d5));
        namedCodepoints.insert("fa-qq", QChar(0xf1d6));
        namedCodepoints.insert("fa-wechat", QChar(0xf1d7)); // alias
        namedCodepoints.insert("fa-weixin", QChar(0xf1d7));
        namedCodepoints.insert("fa-paper-plane", QChar(0xf1d8));
        namedCodepoints.insert("fa-send", QChar(0xf1d8)); // alias
        namedCodepoints.insert("fa-paper-plane-o", QChar(0xf1d9));
        namedCodepoints.insert("fa-send-o", QChar(0xf1d9)); // alias
        namedCodepoints.insert("fa-history", QChar(0xf1da));
        namedCodepoints.insert("fa-circle-thin", QChar(0xf1db));
        namedCodepoints.insert("fa-header", QChar(0xf1dc));
        namedCodepoints.insert("fa-paragraph", QChar(0xf1dd));
        namedCodepoints.insert("fa-sliders", QChar(0xf1de));

        // 0xf1e0
        namedCodepoints.insert("fa-share-alt", QChar(0xf1e0));
        namedCodepoints.insert("fa-share-alt-square", QChar(0xf1e1));
        namedCodepoints.insert("fa-bomb", QChar(0xf1e2));
        namedCodepoints.insert("fa-futbol-o", QChar(0xf1e3));
        namedCodepoints.insert("fa-soccer-ball-o", QChar(0xf1e3)); // alias
        namedCodepoints.insert("fa-tty", QChar(0xf1e4));
        namedCodepoints.insert("fa-binoculars", QChar(0xf1e5));
        namedCodepoints.insert("fa-plug", QChar(0xf1e6));
        namedCodepoints.insert("fa-slideshare", QChar(0xf1e7));
        namedCodepoints.insert("fa-twitch", QChar(0xf1e8));
        namedCodepoints.insert("fa-yelp", QChar(0xf1e9));
        namedCodepoints.insert("fa-newspaper-o", QChar(0xf1ea));
        namedCodepoints.insert("fa-wifi", QChar(0xf1eb));
        namedCodepoints.insert("fa-calculator", QChar(0xf1ec));
        namedCodepoints.insert("fa-paypal", QChar(0xf1ed));
        namedCodepoints.insert("fa-google-wallet", QChar(0xf1ee));

        // 0xf1f0
        namedCodepoints.insert("fa-cc-visa", QChar(0xf1f0));
        namedCodepoints.insert("fa-cc-mastercard", QChar(0xf1f1));
        namedCodepoints.insert("fa-cc-discover", QChar(0xf1f2));
        namedCodepoints.insert("fa-cc-amex", QChar(0xf1f3));
        namedCodepoints.insert("fa-cc-paypal", QChar(0xf1f4));
        namedCodepoints.insert("fa-cc-stripe", QChar(0xf1f5));
        namedCodepoints.insert("fa-bell-slash", QChar(0xf1f6));
        namedCodepoints.insert("fa-bell-slash-o", QChar(0xf1f7));
        namedCodepoints.insert("fa-trash", QChar(0xf1f8));
        namedCodepoints.insert("fa-copyright", QChar(0xf1f9));
        namedCodepoints.insert("fa-at", QChar(0xf1fa));
        namedCodepoints.insert("fa-eyedropper", QChar(0xf1fb));
        namedCodepoints.insert("fa-paint-brush", QChar(0xf1fc));
        namedCodepoints.insert("fa-birthday-cake", QChar(0xf1fd));
        namedCodepoints.insert("fa-area-chart", QChar(0xf1fe));

        // 0xf200
        namedCodepoints.insert("fa-pie-chart", QChar(0xf200));
        namedCodepoints.insert("fa-line-chart", QChar(0xf201));
        namedCodepoints.insert("fa-lastfm", QChar(0xf202));
        namedCodepoints.insert("fa-lastfm-square", QChar(0xf203));
        namedCodepoints.insert("fa-toggle-off", QChar(0xf204));
        namedCodepoints.insert("fa-toggle-on", QChar(0xf205));
        namedCodepoints.insert("fa-bicycle", QChar(0xf206));
        namedCodepoints.insert("fa-bus", QChar(0xf207));
        namedCodepoints.insert("fa-ioxhost", QChar(0xf208));
        namedCodepoints.insert("fa-angellist", QChar(0xf209));
        namedCodepoints.insert("fa-cc", QChar(0xf20a));
        namedCodepoints.insert("fa-ils", QChar(0xf20b));
        namedCodepoints.insert("fa-shekel", QChar(0xf20b)); // alias
        namedCodepoints.insert("fa-sheqel", QChar(0xf20b)); // alias
        namedCodepoints.insert("fa-meanpath", QChar(0xf20c));
    }
}
