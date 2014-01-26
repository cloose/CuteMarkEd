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


static const char* MARKDOWN_CONVERTER = "general/converter";
static const char* FONT_FAMILY_DEFAULT = "Monospace";
static const char* FONT_FAMILY = "editor/font/family";
static const char* FONT_SIZE = "editor/font/size";
static const char* TAB_WIDTH = "editor/tabwidth";
static const char* PROXY_MODE = "internet/proxy/mode";
static const char* PROXY_HOST = "internet/proxy/host";
static const char* PROXY_PORT = "internet/proxy/port";
static const char* PROXY_USER = "internet/proxy/user";
static const char* PROXY_PASSWORD = "internet/proxy/password";
static const char* AUTOLINK_ENABLED = "extensions/autolink";
static const char* STRIKETHROUGH_ENABLED = "extensions/strikethrough";
static const char* ALPHABETICLISTS_ENABLED = "extensions/alphabeticLists";
static const char* DEFINITIONSLISTS_ENABLED = "extensions/definitionLists";
static const char* SMARTYPANTS_ENABLED = "extensions/smartyPants";
static const char* FOOTNOTES_ENABLED = "extensions/footnotes";
static const char* SUPERSCRIPT_ENABLED = "extensions/superscript";
static const char* MATHSUPPORT_ENABLED = "mathsupport/enabled";
static const char* CODEHIGHLIGHT_ENABLED = "codehighlighting/enabled";
static const char* SHOWSPECIALCHARACTERS_ENABLED = "specialchars/enabled";
static const char* WORDWRAP_ENABLED = "wordwrap/enabled";
static const char* SPELLINGCHECK_ENABLED = "spelling/enabled";
static const char* DICTIONARY_LANGUAGE = "spelling/language";

Options::Options(QObject *parent) :
    QObject(parent)
{
}

void Options::apply()
{
    emit proxyConfigurationChanged();
    emit markdownConverterChanged();
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

void Options::readSettings()
{
    QSettings settings;

    // general settings
    m_markdownConverter = (Options::MarkdownConverter)settings.value(MARKDOWN_CONVERTER, 0).toInt();

    // editor settings
    QString fontFamily = settings.value(FONT_FAMILY, FONT_FAMILY_DEFAULT).toString();
    int fontSize = settings.value(FONT_SIZE, 10).toInt();

    m_tabWidth = settings.value(TAB_WIDTH, 8).toInt();

    QFont f(fontFamily, fontSize);
    f.setStyleHint(QFont::TypeWriter);
    setEditorFont(f);

    // proxy settings
    m_proxyMode = (Options::ProxyMode)settings.value(PROXY_MODE, 0).toInt();
    m_proxyHost = settings.value(PROXY_HOST, "").toString();
    m_proxyPort = settings.value(PROXY_PORT, 0).toInt();
    m_proxyUser = settings.value(PROXY_USER, "").toString();
    m_proxyPassword = settings.value(PROXY_PASSWORD, "").toString();

    // extension settings
    m_autolinkEnabled = settings.value(AUTOLINK_ENABLED, true).toBool();
    m_strikethroughEnabled = settings.value(STRIKETHROUGH_ENABLED, true).toBool();
    m_alphabeticListsEnabled = settings.value(ALPHABETICLISTS_ENABLED, true).toBool();
    m_definitionListsEnabled = settings.value(DEFINITIONSLISTS_ENABLED, true).toBool();
    m_smartyPantsEnabled = settings.value(SMARTYPANTS_ENABLED, true).toBool();
    m_footnotesEnabled = settings.value(FOOTNOTES_ENABLED, true).toBool();
    m_superscriptEnabled = settings.value(SUPERSCRIPT_ENABLED, true).toBool();

    m_mathSupportEnabled = settings.value(MATHSUPPORT_ENABLED, false).toBool();
    m_codeHighlightingEnabled = settings.value(CODEHIGHLIGHT_ENABLED, false).toBool();
    m_showSpecialCharactersEnabled = settings.value(SHOWSPECIALCHARACTERS_ENABLED, false).toBool();
    m_wordWrapEnabled = settings.value(WORDWRAP_ENABLED, true).toBool();

    // spelling check settings
    m_spellingCheckEnabled = settings.value(SPELLINGCHECK_ENABLED, true).toBool();
    m_dictionaryLanguage = settings.value(DICTIONARY_LANGUAGE, "en_US").toString();

    apply();
}

void Options::writeSettings()
{
    QSettings settings;

    // general settings
    settings.setValue(MARKDOWN_CONVERTER, m_markdownConverter);

    // editor settings
    settings.setValue(FONT_FAMILY, font.family());
    settings.setValue(FONT_SIZE, font.pointSize());
    settings.setValue(TAB_WIDTH, m_tabWidth);

    // proxy settings
    settings.setValue(PROXY_MODE, m_proxyMode);
    settings.setValue(PROXY_HOST, m_proxyHost);
    settings.setValue(PROXY_PORT, m_proxyPort);
    settings.setValue(PROXY_USER, m_proxyUser);
    settings.setValue(PROXY_PASSWORD, m_proxyPassword);

    // extensions settings
    settings.setValue(AUTOLINK_ENABLED, m_autolinkEnabled);
    settings.setValue(STRIKETHROUGH_ENABLED, m_strikethroughEnabled);
    settings.setValue(ALPHABETICLISTS_ENABLED, m_alphabeticListsEnabled);
    settings.setValue(DEFINITIONSLISTS_ENABLED, m_definitionListsEnabled);
    settings.setValue(SMARTYPANTS_ENABLED, m_smartyPantsEnabled);
    settings.setValue(FOOTNOTES_ENABLED, m_footnotesEnabled);
    settings.setValue(SUPERSCRIPT_ENABLED, m_superscriptEnabled);

    settings.setValue(MATHSUPPORT_ENABLED, m_mathSupportEnabled);
    settings.setValue(CODEHIGHLIGHT_ENABLED, m_codeHighlightingEnabled);
    settings.setValue(SHOWSPECIALCHARACTERS_ENABLED, m_showSpecialCharactersEnabled);
    settings.setValue(WORDWRAP_ENABLED, m_wordWrapEnabled);

    // spelling check settings
    settings.setValue(SPELLINGCHECK_ENABLED, m_spellingCheckEnabled);
    settings.setValue(DICTIONARY_LANGUAGE, m_dictionaryLanguage);
}
