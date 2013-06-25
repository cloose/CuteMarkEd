#include "options.h"
#include <QSettings>

Options::Options(QObject *parent) :
    QObject(parent)
{
}

QFont Options::editorFont() const
{
    return font;
}

void Options::setEditorFont(const QFont &font)
{
    this->font = font;
    emit editorFontChanged(font);
}

void Options::readSettings()
{
    QSettings settings;
    QString fontFamily = settings.value("editor/font/family", "Monospace").toString();
    int fontSize = settings.value("editor/font/size", 10).toInt();

    QFont f(fontFamily, fontSize);
    f.setStyleHint(QFont::TypeWriter);
    setEditorFont(f);
}

void Options::writeSettings()
{
    QSettings settings;
    settings.setValue("editor/font/family", font.family());
    settings.setValue("editor/font/size", font.pointSize());
}
