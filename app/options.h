#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>
#include <QFont>

class Options : public QObject
{
    Q_OBJECT
public:
    explicit Options(QObject *parent = 0);

    QFont editorFont() const;
    void setEditorFont(const QFont &font);

    void readSettings();
    void writeSettings();

signals:
    void editorFontChanged(const QFont &font);

private:
    QFont font;
};

#endif // OPTIONS_H
