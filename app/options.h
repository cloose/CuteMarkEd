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

    bool isCodeHighlightingEnabled() const;
    void setCodeHighlightingEnabled(bool enabled);

    bool isShowSpecialCharactersEnabled() const;
    void setShowSpecialCharactersEnabled(bool enabled);

    bool isWordWrapEnabled() const;
    void setWordWrapEnabled(bool enabled);

    bool isSpellingCheckEnabled() const;
    void setSpellingCheckEnabled(bool enabled);

    QString dictionaryLanguage() const;
    void setDictionaryLanguage(const QString &language);

    MarkdownConverter markdownConverter() const;
    void setMarkdownConverter(MarkdownConverter converter);

    void readSettings();
    void writeSettings();

signals:
    void editorFontChanged(const QFont &font);
    void tabWidthChanged(int tabWidth);
    void proxyConfigurationChanged();
    void markdownConverterChanged();

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
    bool m_codeHighlightingEnabled;
    bool m_showSpecialCharactersEnabled;
    bool m_wordWrapEnabled;
    bool m_spellingCheckEnabled;
    QString m_dictionaryLanguage;
    MarkdownConverter m_markdownConverter;
};

#endif // OPTIONS_H
