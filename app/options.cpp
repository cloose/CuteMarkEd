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

bool Options::isShowSpecialCharactersEnabled() const
{
    return m_showSpecialCharactersEnabled;
}

void Options::setShowSpecialCharactersEnabled(bool enabled)
{
    m_showSpecialCharactersEnabled = enabled;
}

bool Options::isWordWrapEnabled() const
{
    return m_wordWrapEnabled;
}

void Options::setWordWrapEnabled(bool enabled)
{
    m_wordWrapEnabled = enabled;
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

static const char* c_markdownConverter = "general/converter";
static const char* c_fontFamilyDefault = "Monospace";
static const char* c_fontFamily = "editor/font/family";
static const char* c_fontSize = "editor/font/size";
static const char* c_tabWidth = "editor/tabwidth";
static const char* c_proxyMode = "internet/proxy/mode";
static const char* c_proxyHost = "internet/proxy/host";
static const char* c_proxyPort = "internet/proxy/port";
static const char* c_proxyUser = "internet/proxy/user";
static const char* c_proxyPassword = "internet/proxy/password";
static const char* c_autolinkEnabled = "extensions/autolink";
static const char* c_strikethroughEnabled = "extensions/strikethrough";
static const char* c_alphabeticListsEnabled = "extensions/alphabeticLists";
static const char* c_definitionListsEnabled = "extensions/definitionLists";
static const char* c_smartyPantsEnabled = "extensions/smartyPants";
static const char* c_footnotesEnabled = "extensions/footnotes";
static const char* c_superscriptEnabled = "extensions/superscript";
static const char* c_mathSupportEnabled = "mathsupport/enabled";
static const char* c_codeHighlightingEnabled = "codehighlighting/enabled";
static const char* c_showSpecialCharactersEnabled = "specialchars/enabled";
static const char* c_wordWrapEnabled = "wordwrap/enabled";
static const char* c_spellingCheckEnabled = "spelling/enabled";
static const char* c_dictionaryLanguage = "spelling/language";

void Options::readSettings()
{
    QSettings settings;

    // general settings
    m_markdownConverter = (Options::MarkdownConverter)settings.value(c_markdownConverter, 0).toInt();

    // editor settings
    QString fontFamily = settings.value(c_fontFamily, c_fontFamilyDefault).toString();
    int fontSize = settings.value(c_fontSize, 10).toInt();

    m_tabWidth = settings.value(c_tabWidth, 8).toInt();

    QFont f(fontFamily, fontSize);
    f.setStyleHint(QFont::TypeWriter);
    setEditorFont(f);

    // proxy settings
    m_proxyMode = (Options::ProxyMode)settings.value(c_proxyMode, 0).toInt();
    m_proxyHost = settings.value(c_proxyHost, "").toString();
    m_proxyPort = settings.value(c_proxyPort, 0).toInt();
    m_proxyUser = settings.value(c_proxyUser, "").toString();
    m_proxyPassword = settings.value(c_proxyPassword, "").toString();

    // extension settings
    m_autolinkEnabled = settings.value(c_autolinkEnabled, true).toBool();
    m_strikethroughEnabled = settings.value(c_strikethroughEnabled, true).toBool();
    m_alphabeticListsEnabled = settings.value(c_alphabeticListsEnabled, true).toBool();
    m_definitionListsEnabled = settings.value(c_definitionListsEnabled, true).toBool();
    m_smartyPantsEnabled = settings.value(c_smartyPantsEnabled, true).toBool();
    m_footnotesEnabled = settings.value(c_footnotesEnabled, true).toBool();
    m_superscriptEnabled = settings.value(c_superscriptEnabled, true).toBool();

    m_mathSupportEnabled = settings.value(c_mathSupportEnabled, false).toBool();
    m_codeHighlightingEnabled = settings.value(c_codeHighlightingEnabled, false).toBool();
    m_showSpecialCharactersEnabled = settings.value(c_showSpecialCharactersEnabled, false).toBool();
    m_wordWrapEnabled = settings.value(c_wordWrapEnabled, false).toBool();

    // spelling check settings
    m_spellingCheckEnabled = settings.value(c_spellingCheckEnabled, true).toBool();
    m_dictionaryLanguage = settings.value(c_dictionaryLanguage, "en_US").toString();

    apply();
}

void Options::writeSettings()
{
    QSettings settings;

    // general settings
    settings.setValue(c_markdownConverter, m_markdownConverter);

    // editor settings
    settings.setValue(c_fontFamily, font.family());
    if(font.pointSize()!=10) settings.setValue(c_fontSize, font.pointSize());
    if(m_tabWidth!=8) settings.setValue(c_tabWidth, m_tabWidth);

    // proxy settings
    settings.setValue(c_proxyMode, m_proxyMode);
    if(!m_proxyHost.isEmpty()) settings.setValue(c_proxyHost, m_proxyHost);
    if( m_proxyPort!=0) settings.setValue(c_proxyPort, m_proxyPort);
    if(!m_proxyUser.isEmpty()) settings.setValue(c_proxyUser, m_proxyUser);
    if(!m_proxyPassword.isEmpty()) settings.setValue(c_proxyPassword, m_proxyPassword);

    // extensions settings
    settings.setValue(c_autolinkEnabled, m_autolinkEnabled);
    settings.setValue(c_strikethroughEnabled, m_strikethroughEnabled);
    settings.setValue(c_alphabeticListsEnabled, m_alphabeticListsEnabled);
    settings.setValue(c_definitionListsEnabled, m_definitionListsEnabled);
    settings.setValue(c_smartyPantsEnabled, m_smartyPantsEnabled);
    settings.setValue(c_footnotesEnabled, m_footnotesEnabled);
    settings.setValue(c_superscriptEnabled, m_superscriptEnabled);

    settings.setValue(c_mathSupportEnabled, m_mathSupportEnabled);
    settings.setValue(c_codeHighlightingEnabled, m_codeHighlightingEnabled);
    settings.setValue(c_showSpecialCharactersEnabled, m_showSpecialCharactersEnabled);
    settings.setValue(c_wordWrapEnabled, m_wordWrapEnabled);

    // spelling check settings
    settings.setValue(c_spellingCheckEnabled, m_spellingCheckEnabled);
    settings.setValue(c_dictionaryLanguage, m_dictionaryLanguage);
}
