#include "fontawesomeiconengineplugin.h"

#include "fontawesomeiconengine.h"

FontAwesomeIconEnginePlugin::FontAwesomeIconEnginePlugin(QObject *parent) :
    QIconEnginePlugin(parent)
{
}

QStringList FontAwesomeIconEnginePlugin::keys() const
{
    QStringList keys(QLatin1String("fontawesome"));
    return keys;
}

QIconEngine *FontAwesomeIconEnginePlugin::create(const QString &filename)
{
    FontAwesomeIconEngine *engine = new FontAwesomeIconEngine;
    if (!filename.isNull()) {
        int lastPoint = filename.lastIndexOf(".");
        engine->setIconName(filename.left(lastPoint));
    }
    return engine;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(fontawesomeicon, FontAwesomeIconEnginePlugin)
#endif // QT_VERSION < 0x050000
