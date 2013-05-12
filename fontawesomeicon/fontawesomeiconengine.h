#ifndef FONTAWESOMEICONENGINE_H
#define FONTAWESOMEICONENGINE_H

#include <QIconEngine>

class FontAwesomeIconEngine : public QIconEngine
{
public:
    FontAwesomeIconEngine();
    FontAwesomeIconEngine(const QString &iconName);

    void setIconName(const QString &iconName);

    QIconEngine *clone() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) Q_DECL_OVERRIDE;
    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) Q_DECL_OVERRIDE;

private:
    void loadFont();

    QString iconName;

    static int fontId;
    static QString fontName;
    static QHash<QString, QChar> namedCodepoints;
};

#endif // FONTAWESOMEICONENGINE_H
