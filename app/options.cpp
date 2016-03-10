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

#include <QWebSettings>


static const char* MARKDOWN_CONVERTER = "General/converter";
static const char* LAST_USED_THEME = "General/lastusedtheme";
static const char* THEME_DEFAULT = "Default";
static const char* FONT_FAMILY_DEFAULT = "Monospace";
static const char* FONT_FAMILY = "editor/font/family";
static const char* FONT_SIZE = "editor/font/size";
static const char* TAB_WIDTH = "editor/tabwidth";
static const char* LINECOLUMN_ENABLED = "editor/linecolumn/enabled";
static const char* RULER_ENABLED = "editor/ruler/enabled";
static const char* RULER_POS = "editor/ruler/pos";
static const char* PREVIEW_STANDARD_FONT = "preview/standardfont";
static const char* PREVIEW_FIXED_FONT = "preview/fixedfont";
static const char* PREVIEW_SERIF_FONT = "preview/seriffont";
static const char* PREVIEW_SANSSERIF_FONT = "preview/sansseriffont";
static const char* PREVIEW_DEFAULT_FONT_SIZE = "preview/defaultfontsize";
static const char* PREVIEW_DEFAULT_FIXED_FONT_SIZE = "preview/defaultfixedfontsize";
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
static const char* MATHINLINESUPPORT_ENABLED = "mathinlinesupport/enabled";
static const char* CODEHIGHLIGHT_ENABLED = "codehighlighting/enabled";
static const char* SHOWSPECIALCHARACTERS_ENABLED = "specialchars/enabled";
static const char* WORDWRAP_ENABLED = "wordwrap/enabled";
static const char* SOURCEATSINGLESIZE_ENABLED = "sourceatsinglesize/enabled";
static const char* SPELLINGCHECK_ENABLED = "spelling/enabled";
static const char* DICTIONARY_LANGUAGE = "spelling/language";
static const char* YAMLHEADERSUPPORT_ENABLED = "yamlheadersupport/enabled";
static const char* DIAGRAMSUPPORT_ENABLED = "diagramsupport/enabled";

static const char* DEPRECATED__LAST_USED_STYLE = "general/lastusedstyle";

Options::Options(QObject *parent) :
    QObject(parent),
    m_tabWidth(8),
    m_proxyMode(NoProxy),
    m_proxyPort(0),
    m_autolinkEnabled(true),
    m_strikethroughEnabled(true),
    m_alphabeticListsEnabled(true),
    m_definitionListsEnabled(true),
    m_smartyPantsEnabled(true),
    m_footnotesEnabled(true),
    m_superscriptEnabled(true),
    m_mathSupportEnabled(false),
    m_mathInlineSupportEnabled(false),
    m_codeHighlightingEnabled(false),
    m_showSpecialCharactersEnabled(false),
    m_wordWrapEnabled(true),
    m_sourceAtSingleSizeEnabled(true),
    m_spellingCheckEnabled(true),
    m_diagramSupportEnabled(false),
    m_lineColumnEnabled(true),
    m_rulerEnabled(false),
    m_rulerPos(80),
    m_markdownConverter(DiscountMarkdownConverter),
    m_lastUsedTheme(THEME_DEFAULT)
{
}

void Options::apply()
{
    QWebSettings *globalWebSettings = QWebSettings::globalSettings();
    globalWebSettings->setFontFamily(QWebSettings::StandardFont, m_standardFontFamily);
    globalWebSettings->setFontFamily(QWebSettings::FixedFont, m_fixedFontFamily);
    globalWebSettings->setFontFamily(QWebSettings::SerifFont, m_serifFontFamily);
    globalWebSettings->setFontFamily(QWebSettings::SansSerifFont, m_sansSerifFontFamily);
    globalWebSettings->setFontSize(QWebSettings::DefaultFontSize, m_defaultFontSize);
    globalWebSettings->setFontSize(QWebSettings::DefaultFixedFontSize, m_defaultFixedFontSize);

    emit proxyConfigurationChanged();
    emit markdownConverterChanged();
    emit lineColumnEnabledChanged(m_lineColumnEnabled);
    emit rulerEnabledChanged(m_rulerEnabled);
    emit rulerPosChanged(m_rulerPos);
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

bool Options::isLineColumnEnabled() const
{
    return m_lineColumnEnabled;
}

void Options::setLineColumnEnabled(bool enabled)
{
    m_lineColumnEnabled = enabled;
    emit lineColumnEnabledChanged(enabled);
}

bool Options::isRulerEnabled() const
{
    return m_rulerEnabled;
}

void Options::setRulerEnabled(bool enabled)
{
    m_rulerEnabled = enabled;
    emit rulerEnabledChanged(enabled);
}

int Options::rulerPos() const
{
    return m_rulerPos;
}

void Options::setRulerPos(int pos)
{
    m_rulerPos = pos;
    emit rulerPosChanged(pos);
}

QFont Options::standardFont() const
{
    return QFont(m_standardFontFamily);
}

void Options::setStandardFont(const QFont &font)
{
    m_standardFontFamily = font.family();
}

QFont Options::serifFont() const
{
    return QFont(m_serifFontFamily);
}

void Options::setSerifFont(const QFont &font)
{
    m_serifFontFamily = font.family();
}

QFont Options::sansSerifFont() const
{
    return QFont(m_sansSerifFontFamily);
}

void Options::setSansSerifFont(const QFont &font)
{
    m_sansSerifFontFamily = font.family();
}

QFont Options::fixedFont() const
{
    return QFont(m_fixedFontFamily);
}

void Options::setFixedFont(const QFont &font)
{
    m_fixedFontFamily = font.family();
}

int Options::defaultFontSize() const
{
    return m_defaultFontSize;
}

void Options::setDefaultFontSize(int size)
{
    m_defaultFontSize = size;
}

int Options::defaultFixedFontSize() const
{
    return m_defaultFixedFontSize;
}

void Options::setDefaultFixedFontSize(int size)
{
    m_defaultFixedFontSize = size;
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

void Options::addCustomShortcut(const QString &actionName, const QKeySequence &keySequence)
{
    if (actionName.isEmpty()) return;
    m_customShortcuts.insert(actionName, keySequence);
}

bool Options::hasCustomShortcut(const QString &actionName) const
{
    return m_customShortcuts.contains(actionName);
}

QKeySequence Options::customShortcut(const QString &actionName) const
{
    return m_customShortcuts.value(actionName);
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

bool Options::isMathInlineSupportEnabled() const
{
    return m_mathInlineSupportEnabled;
}

void Options::setMathInlineSupportEnabled(bool enabled)
{
    m_mathInlineSupportEnabled = enabled;
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

bool Options::isSourceAtSingleSizeEnabled() const
{
    return m_sourceAtSingleSizeEnabled;
}

void Options::setSourceAtSingleSizeEnabled(bool enabled)
{
    m_sourceAtSingleSizeEnabled = enabled;
    emit editorStyleChanged();
}

bool Options::isSpellingCheckEnabled() const
{
    return m_spellingCheckEnabled;
}

void Options::setSpellingCheckEnabled(bool enabled)
{
    m_spellingCheckEnabled = enabled;
}

bool Options::isYamlHeaderSupportEnabled() const
{
    return m_yamlHeaderSupportEnabled;
}

void Options::setYamlHeaderSupportEnabled(bool enabled)
{
    m_yamlHeaderSupportEnabled = enabled;
}

bool Options::isDiagramSupportEnabled() const
{
    return m_diagramSupportEnabled;
}

void Options::setDiagramSupportEnabled(bool enabled)
{
    m_diagramSupportEnabled = enabled;
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

QString Options::lastUsedTheme() const
{
    return m_lastUsedTheme;
}

void Options::setLastUsedTheme(const QString &theme)
{
    m_lastUsedTheme = theme;
}

void Options::readSettings()
{
    QSettings settings;

    // general settings
    m_markdownConverter = (Options::MarkdownConverter)settings.value(MARKDOWN_CONVERTER, 0).toInt();
    m_lastUsedTheme = settings.value(LAST_USED_THEME, THEME_DEFAULT).toString();

    // editor settings
    QString fontFamily = settings.value(FONT_FAMILY, FONT_FAMILY_DEFAULT).toString();
    int fontSize = settings.value(FONT_SIZE, 10).toInt();

    m_tabWidth = settings.value(TAB_WIDTH, 8).toInt();
    m_lineColumnEnabled = settings.value(LINECOLUMN_ENABLED, false).toBool();
    m_rulerEnabled = settings.value(RULER_ENABLED, false).toBool();
    m_rulerPos = settings.value(RULER_POS, 80).toInt();

    QFont f(fontFamily, fontSize);
    f.setStyleHint(QFont::TypeWriter);
    setEditorFont(f);

    // html preview settings
    QWebSettings *globalWebSettings = QWebSettings::globalSettings();
    m_standardFontFamily = settings.value(PREVIEW_STANDARD_FONT, globalWebSettings->fontFamily(QWebSettings::StandardFont)).toString();
    m_fixedFontFamily = settings.value(PREVIEW_FIXED_FONT, globalWebSettings->fontFamily(QWebSettings::FixedFont)).toString();
    m_serifFontFamily = settings.value(PREVIEW_SERIF_FONT, globalWebSettings->fontFamily(QWebSettings::SerifFont)).toString();
    m_sansSerifFontFamily = settings.value(PREVIEW_SANSSERIF_FONT, globalWebSettings->fontFamily(QWebSettings::SansSerifFont)).toString();
    m_defaultFontSize = settings.value(PREVIEW_DEFAULT_FONT_SIZE, globalWebSettings->fontSize(QWebSettings::DefaultFontSize)).toInt();
    m_defaultFixedFontSize = settings.value(PREVIEW_DEFAULT_FIXED_FONT_SIZE, globalWebSettings->fontSize(QWebSettings::DefaultFixedFontSize)).toInt();
    m_mathInlineSupportEnabled = settings.value(MATHINLINESUPPORT_ENABLED, false).toBool();

    // proxy settings
    m_proxyMode = (Options::ProxyMode)settings.value(PROXY_MODE, 0).toInt();
    m_proxyHost = settings.value(PROXY_HOST, "").toString();
    m_proxyPort = settings.value(PROXY_PORT, 0).toInt();
    m_proxyUser = settings.value(PROXY_USER, "").toString();
    m_proxyPassword = settings.value(PROXY_PASSWORD, "").toString();

    // shortcut settings
    settings.beginGroup("shortcuts");
    foreach (QString actionName, settings.childKeys()) {
        QKeySequence keySequence = settings.value(actionName, "").value<QKeySequence>();
        addCustomShortcut(actionName, keySequence);
    }
    settings.endGroup();

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
    m_sourceAtSingleSizeEnabled = settings.value(SOURCEATSINGLESIZE_ENABLED, true).toBool();
    m_yamlHeaderSupportEnabled = settings.value(YAMLHEADERSUPPORT_ENABLED, false).toBool();
    m_diagramSupportEnabled = settings.value(DIAGRAMSUPPORT_ENABLED, false).toBool();

    // spelling check settings
    m_spellingCheckEnabled = settings.value(SPELLINGCHECK_ENABLED, true).toBool();
    m_dictionaryLanguage = settings.value(DICTIONARY_LANGUAGE, "en_US").toString();

    // migrate deprecated lastUsedStyle option
    if (settings.contains(DEPRECATED__LAST_USED_STYLE)) {
        migrateLastUsedStyleOption(settings);
    }

    apply();
}

void Options::writeSettings()
{
    QSettings settings;

    // general settings
    settings.setValue(MARKDOWN_CONVERTER, m_markdownConverter);
    settings.setValue(LAST_USED_THEME, m_lastUsedTheme);

    // editor settings
    settings.setValue(FONT_FAMILY, font.family());
    settings.setValue(FONT_SIZE, font.pointSize());
    settings.setValue(TAB_WIDTH, m_tabWidth);
    settings.setValue(LINECOLUMN_ENABLED, m_lineColumnEnabled);
    settings.setValue(RULER_ENABLED, m_rulerEnabled);
    settings.setValue(RULER_POS, m_rulerPos);

    // html preview settings
    settings.setValue(PREVIEW_STANDARD_FONT, m_standardFontFamily);
    settings.setValue(PREVIEW_FIXED_FONT, m_fixedFontFamily);
    settings.setValue(PREVIEW_SERIF_FONT, m_serifFontFamily);
    settings.setValue(PREVIEW_SANSSERIF_FONT, m_sansSerifFontFamily);
    settings.setValue(PREVIEW_DEFAULT_FONT_SIZE, m_defaultFontSize);
    settings.setValue(PREVIEW_DEFAULT_FIXED_FONT_SIZE, m_defaultFixedFontSize);
    settings.setValue(MATHINLINESUPPORT_ENABLED, m_mathInlineSupportEnabled);

    // proxy settings
    settings.setValue(PROXY_MODE, m_proxyMode);
    settings.setValue(PROXY_HOST, m_proxyHost);
    settings.setValue(PROXY_PORT, m_proxyPort);
    settings.setValue(PROXY_USER, m_proxyUser);
    settings.setValue(PROXY_PASSWORD, m_proxyPassword);

    // shortcut settings
    settings.beginGroup("shortcuts");
    QMap<QString, QKeySequence>::const_iterator it = m_customShortcuts.constBegin();
    while (it != m_customShortcuts.constEnd()) {
        settings.setValue(it.key(), it.value());
        ++it;
    }
    settings.endGroup();

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
    settings.setValue(SOURCEATSINGLESIZE_ENABLED, m_sourceAtSingleSizeEnabled);
    settings.setValue(YAMLHEADERSUPPORT_ENABLED, m_yamlHeaderSupportEnabled);
    settings.setValue(DIAGRAMSUPPORT_ENABLED, m_diagramSupportEnabled);

    // spelling check settings
    settings.setValue(SPELLINGCHECK_ENABLED, m_spellingCheckEnabled);
    settings.setValue(DICTIONARY_LANGUAGE, m_dictionaryLanguage);
}

void Options::migrateLastUsedStyleOption(QSettings &settings)
{
    static const QMap<QString, QString> migrations {
        { "actionDefault", "Default" },
        { "actionGithub", "Github" },
        { "actionSolarizedLight", "Solarized Light" },
        { "actionSolarizedDark", "Solarized Dark" },
        { "actionClearness", "Clearness" },
        { "actionClearnessDark", "Clearness Dark" },
        { "actionBywordDark", "Byword Dark" }
    };

    QString lastUsedStyle = settings.value(DEPRECATED__LAST_USED_STYLE).toString();
    m_lastUsedTheme = migrations[lastUsedStyle];

    settings.remove(DEPRECATED__LAST_USED_STYLE);
}
