#ifndef FONTAWESOMEICONENGINEPLUGIN_H
#define FONTAWESOMEICONENGINEPLUGIN_H

#include <QIconEnginePlugin>


class FontAwesomeIconEnginePlugin : public QIconEnginePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QIconEngineFactoryInterface" FILE "fontawesomeicon.json")
    
public:
    FontAwesomeIconEnginePlugin(QObject *parent = 0);

    QStringList keys() const Q_DECL_OVERRIDE;
    QIconEngine *create(const QString &filename = QString()) Q_DECL_OVERRIDE;
};

#endif // FONTAWESOMEICONENGINEPLUGIN_H
