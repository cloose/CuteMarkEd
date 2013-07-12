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

Options::ProxyMode Options::proxyMode() const
{
    return m_proxyMode;
}

void Options::setProxyMode(Options::ProxyMode mode)
{
    m_proxyMode = mode;
    emit proxyConfigurationChanged();
}

QString Options::proxyHost() const
{
    return m_proxyHost;
}

void Options::setProxyHost(const QString &host)
{
    m_proxyHost = host;
}

quint16 Options::proxyPort() const
{
    return m_proxyPort;
}

void Options::setProxyPort(quint16 port)
{
    m_proxyPort = port;
}

QString Options::proxyUser() const
{
    return m_proxyUser;
}

void Options::setProxyUser(const QString &user)
{
    m_proxyUser = user;
}

QString Options::proxyPassword() const
{
    return m_proxyPassword;
}

void Options::setProxyPassword(const QString &password)
{
    m_proxyPassword = password;
}

bool Options::isAutolinkEnabled() const
{
    return m_autolinkEnabled;
}

void Options::setAutolinkEnabled(bool enabled)
{
    m_autolinkEnabled = enabled;
}

bool Options::isStrikethroughEnabled() const
{
    return m_strikethroughEnabled;
}

void Options::setStrikethroughEnabled(bool enabled)
{
    m_strikethroughEnabled = enabled;
}

void Options::readSettings()
{
    QSettings settings;

    // editor settings
    QString fontFamily = settings.value("editor/font/family", "Monospace").toString();
    int fontSize = settings.value("editor/font/size", 10).toInt();

    QFont f(fontFamily, fontSize);
    f.setStyleHint(QFont::TypeWriter);
    setEditorFont(f);

    // proxy settings
    setProxyMode((Options::ProxyMode)settings.value("internet/proxy/mode", 0).toInt());
    m_proxyHost = settings.value("internet/proxy/host", "").toString();
    m_proxyPort = settings.value("internet/proxy/port", 0).toInt();
    m_proxyUser = settings.value("internet/proxy/user", "").toString();
    m_proxyPassword = settings.value("internet/proxy/password", "").toString();

    // extension settings
    m_autolinkEnabled = settings.value("extensions/autolink", true).toBool();
    m_strikethroughEnabled = settings.value("extensions/strikethrough", true).toBool();
}

void Options::writeSettings()
{
    QSettings settings;

    // editor settings
    settings.setValue("editor/font/family", font.family());
    settings.setValue("editor/font/size", font.pointSize());

    // proxy settings
    settings.setValue("internet/proxy/mode", m_proxyMode);
    settings.setValue("internet/proxy/host", m_proxyHost);
    settings.setValue("internet/proxy/port", m_proxyPort);
    settings.setValue("internet/proxy/user", m_proxyUser);
    settings.setValue("internet/proxy/password", m_proxyPassword);

    // extensions settings
    settings.setValue("extensions/autolink", m_autolinkEnabled);
    settings.setValue("extensions/strikethrough", m_strikethroughEnabled);
}
