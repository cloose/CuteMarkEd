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

void Options::apply()
{
    emit proxyConfigurationChanged();
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

int Options::tabWidth() const
{
    return m_tabWidth;
}

void Options::setTabWidth(int width)
{
    m_tabWidth = width;
    emit tabWidthChanged(width);
}

Options::ProxyMode Options::proxyMode() const
{
    return m_proxyMode;
}

void Options::setProxyMode(Options::ProxyMode mode)
{
    m_proxyMode = mode;
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

bool Options::isAlphabeticListsEnabled() const
{
    return m_alphabeticListsEnabled;
}

void Options::setAlphabeticListsEnabled(bool enabled)
{
    m_alphabeticListsEnabled = enabled;
}

bool Options::isDefinitionListsEnabled() const
{
    return m_definitionListsEnabled;
}

void Options::setDefinitionListsEnabled(bool enabled)
{
    m_definitionListsEnabled = enabled;
}

bool Options::isSmartyPantsEnabled() const
{
    return m_smartyPantsEnabled;
}

void Options::setSmartyPantsEnabled(bool enabled)
{
    m_smartyPantsEnabled = enabled;
}

bool Options::isFootnotesEnabled() const
{
    return m_footnotesEnabled;
}

void Options::setFootnotesEnabled(bool enabled)
{
    m_footnotesEnabled = enabled;
}

bool Options::isSuperscriptEnabled() const
{
    return m_superscriptEnabled;
}

void Options::setSuperscriptEnabled(bool enabled)
{
    m_superscriptEnabled = enabled;
}

bool Options::isMathSupportEnabled() const
{
    return m_mathSupportEnabled;
}

void Options::setMathSupportEnabled(bool enabled)
{
    m_mathSupportEnabled = enabled;
}

bool Options::isCodeHighlightingEnabled() const
{
    return m_codeHighlightingEnabled;
}

void Options::setCodeHighlightingEnabled(bool enabled)
{
    m_codeHighlightingEnabled = enabled;
}

bool Options::isSpellingCheckEnabled() const
{
    return m_spellingCheckEnabled;
}

void Options::setSpellingCheckEnabled(bool enabled)
{
    m_spellingCheckEnabled = enabled;
}

QString Options::dictionaryLanguage() const
{
    return m_dictionaryLanguage;
}

void Options::setDictionaryLanguage(const QString &language)
{
    m_dictionaryLanguage = language;
}

Options::MarkdownConverter Options::markdownConverter() const
{
    return m_markdownConverter;
}

void Options::setMarkdownConverter(Options::MarkdownConverter converter)
{
    if (m_markdownConverter != converter) {
        m_markdownConverter = converter;
        emit markdownConverterChanged();
    }
}

void Options::readSettings()
{
    QSettings settings;

    // general settings
    m_markdownConverter = (Options::MarkdownConverter)settings.value("general/converter", 0).toInt();

    // editor settings
    QString fontFamily = settings.value("editor/font/family", "Monospace").toString();
    int fontSize = settings.value("editor/font/size", 10).toInt();

    m_tabWidth = settings.value("editor/tabwidth", 8).toInt();

    QFont f(fontFamily, fontSize);
    f.setStyleHint(QFont::TypeWriter);
    setEditorFont(f);

    // proxy settings
    m_proxyMode = (Options::ProxyMode)settings.value("internet/proxy/mode", 0).toInt();
    m_proxyHost = settings.value("internet/proxy/host", "").toString();
    m_proxyPort = settings.value("internet/proxy/port", 0).toInt();
    m_proxyUser = settings.value("internet/proxy/user", "").toString();
    m_proxyPassword = settings.value("internet/proxy/password", "").toString();

    // extension settings
    m_autolinkEnabled = settings.value("extensions/autolink", true).toBool();
    m_strikethroughEnabled = settings.value("extensions/strikethrough", true).toBool();
    m_alphabeticListsEnabled = settings.value("extensions/alphabeticLists", true).toBool();
    m_definitionListsEnabled = settings.value("extensions/definitionLists", true).toBool();
    m_smartyPantsEnabled = settings.value("extensions/smartyPants", true).toBool();
    m_footnotesEnabled = settings.value("extensions/footnotes", true).toBool();
    m_superscriptEnabled = settings.value("extensions/superscript", true).toBool();

    m_mathSupportEnabled = settings.value("mathsupport/enabled", false).toBool();
    m_codeHighlightingEnabled = settings.value("codehighlighting/enabled", false).toBool();

    // spelling check settings
    m_spellingCheckEnabled = settings.value("spelling/enabled", true).toBool();
    m_dictionaryLanguage = settings.value("spelling/language", "en_US").toString();

    apply();
}

void Options::writeSettings()
{
    QSettings settings;

    // general settings
    settings.setValue("general/converter", m_markdownConverter);

    // editor settings
    settings.setValue("editor/font/family", font.family());
    settings.setValue("editor/font/size", font.pointSize());
    settings.setValue("editor/tabwidth", m_tabWidth);

    // proxy settings
    settings.setValue("internet/proxy/mode", m_proxyMode);
    settings.setValue("internet/proxy/host", m_proxyHost);
    settings.setValue("internet/proxy/port", m_proxyPort);
    settings.setValue("internet/proxy/user", m_proxyUser);
    settings.setValue("internet/proxy/password", m_proxyPassword);

    // extensions settings
    settings.setValue("extensions/autolink", m_autolinkEnabled);
    settings.setValue("extensions/strikethrough", m_strikethroughEnabled);
    settings.setValue("extensions/alphabeticLists", m_alphabeticListsEnabled);
    settings.setValue("extensions/definitionLists", m_definitionListsEnabled);
    settings.setValue("extensions/smartyPants", m_smartyPantsEnabled);
    settings.setValue("extensions/footnotes", m_footnotesEnabled);
    settings.setValue("extensions/superscript", m_superscriptEnabled);

    settings.setValue("mathsupport/enabled", m_mathSupportEnabled);
    settings.setValue("codehighlighting/enabled", m_codeHighlightingEnabled);

    // spelling check settings
    settings.setValue("spelling/enabled", m_spellingCheckEnabled);
    settings.setValue("spelling/language", m_dictionaryLanguage);
}
