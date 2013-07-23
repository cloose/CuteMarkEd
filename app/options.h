/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
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
#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>
#include <QFont>

class Options : public QObject
{
    Q_OBJECT
public:
    enum ProxyMode { NoProxy, SystemProxy, ManualProxy };

    explicit Options(QObject *parent = 0);

    void apply();

    QFont editorFont() const;
    void setEditorFont(const QFont &font);

    ProxyMode proxyMode() const;
    void setProxyMode(ProxyMode mode);

    QString proxyHost() const;
    void setProxyHost(const QString &host);

    quint16 proxyPort() const;
    void setProxyPort(quint16 port);

    QString proxyUser() const;
    void setProxyUser(const QString &user);

    QString proxyPassword() const;
    void setProxyPassword(const QString &password);

    bool isAutolinkEnabled() const;
    void setAutolinkEnabled(bool enabled);

    bool isStrikethroughEnabled() const;
    void setStrikethroughEnabled(bool enabled);

    bool isAlphabeticListsEnabled() const;
    void setAlphabeticListsEnabled(bool enabled);

    bool isDefinitionListsEnabled() const;
    void setDefinitionListsEnabled(bool enabled);

    bool isSmartyPantsEnabled() const;
    void setSmartyPantsEnabled(bool enabled);

    void readSettings();
    void writeSettings();

signals:
    void editorFontChanged(const QFont &font);
    void proxyConfigurationChanged();

private:
    QFont font;
    ProxyMode m_proxyMode;
    QString m_proxyHost;
    quint16 m_proxyPort;
    QString m_proxyUser;
    QString m_proxyPassword;
    bool m_autolinkEnabled;
    bool m_strikethroughEnabled;
    bool m_alphabeticListsEnabled;
    bool m_definitionListsEnabled;
    bool m_smartyPantsEnabled;
};

#endif // OPTIONS_H
