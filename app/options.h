/*
 * Copyright 2013-2015 Christian Loose <christian.loose@hamburg.de>
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
#include <QKeySequence>
#include <QMap>
#include <QSettings>

class Options : public QObject
{
    Q_OBJECT
public:
    enum ProxyMode { NoProxy, SystemProxy, ManualProxy };
#ifndef ENABLE_HOEDOWN
    enum MarkdownConverter { DiscountMarkdownConverter, RevealMarkdownConverter };
#else
    enum MarkdownConverter { DiscountMarkdownConverter, HoedownMarkdownConverter, RevealMarkdownConverter };
#endif

    explicit Options(QObject *parent = 0);

    void apply();

    /* Editor options */
    QFont editorFont() const;
    void setEditorFont(const QFont &font);

    int tabWidth() const;
    void setTabWidth(int width);

    bool isLineColumnEnabled() const;
    void setLineColumnEnabled(bool enabled);

    bool isRulerEnabled() const;
    void setRulerEnabled(bool enabled);

    int rulerPos() const;
    void setRulerPos(int pos);

    /* HTML preview options */
    QFont standardFont() const;
    void setStandardFont(const QFont &font);

    QFont serifFont() const;
    void setSerifFont(const QFont &font);

    QFont sansSerifFont() const;
    void setSansSerifFont(const QFont &font);

    QFont fixedFont() const;
    void setFixedFont(const QFont &font);

    int defaultFontSize() const;
    void setDefaultFontSize(int size);

    int defaultFixedFontSize() const;
    void setDefaultFixedFontSize(int size);

    /* Internet options */
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

    /* Shortcuts options */
    void addCustomShortcut(const QString &actionName, const QKeySequence &keySequence);
    bool hasCustomShortcut(const QString &actionName) const;
    QKeySequence customShortcut(const QString &actionName) const;

    /* Extra menu options */
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

    bool isFootnotesEnabled() const;
    void setFootnotesEnabled(bool enabled);

    bool isSuperscriptEnabled() const;
    void setSuperscriptEnabled(bool enabled);

    bool isMathSupportEnabled() const;
    void setMathSupportEnabled(bool enabled);

    bool isMathInlineSupportEnabled() const;
    void setMathInlineSupportEnabled(bool enabled);

    bool isCodeHighlightingEnabled() const;
    void setCodeHighlightingEnabled(bool enabled);

    bool isShowSpecialCharactersEnabled() const;
    void setShowSpecialCharactersEnabled(bool enabled);

    bool isWordWrapEnabled() const;
    void setWordWrapEnabled(bool enabled);

    bool isSourceAtSingleSizeEnabled() const;
    void setSourceAtSingleSizeEnabled(bool enabled);

    bool isSpellingCheckEnabled() const;
    void setSpellingCheckEnabled(bool enabled);

    bool isYamlHeaderSupportEnabled() const;
    void setYamlHeaderSupportEnabled(bool enabled);

    bool isDiagramSupportEnabled() const;
    void setDiagramSupportEnabled(bool enabled);

    QString dictionaryLanguage() const;
    void setDictionaryLanguage(const QString &language);

    MarkdownConverter markdownConverter() const;
    void setMarkdownConverter(MarkdownConverter converter);

    QString lastUsedTheme() const;
    void setLastUsedTheme(const QString &theme);

    void readSettings();
    void writeSettings();

signals:
    void editorFontChanged(const QFont &font);
    void editorStyleChanged();
    void tabWidthChanged(int tabWidth);
    void lineColumnEnabledChanged(bool enabled);
    void rulerEnabledChanged(bool enabled);
    void rulerPosChanged(int pos);

    void proxyConfigurationChanged();
    void markdownConverterChanged();

private:
    void migrateLastUsedStyleOption(QSettings &settings);

private:
    QFont font;
    int m_tabWidth;
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
    bool m_footnotesEnabled;
    bool m_superscriptEnabled;
    bool m_mathSupportEnabled;
    bool m_mathInlineSupportEnabled;
    bool m_codeHighlightingEnabled;
    bool m_showSpecialCharactersEnabled;
    bool m_wordWrapEnabled;
    bool m_sourceAtSingleSizeEnabled;
    bool m_spellingCheckEnabled;
    bool m_yamlHeaderSupportEnabled;
    bool m_diagramSupportEnabled;
    bool m_lineColumnEnabled;
    bool m_rulerEnabled;
    int m_rulerPos;
    QString m_dictionaryLanguage;
    MarkdownConverter m_markdownConverter;
    QString m_lastUsedTheme;
    QString m_standardFontFamily;
    QString m_fixedFontFamily;
    QString m_serifFontFamily;
    QString m_sansSerifFontFamily;
    int m_defaultFontSize;
    int m_defaultFixedFontSize;
    QMap<QString, QKeySequence> m_customShortcuts;
};

#endif // OPTIONS_H
