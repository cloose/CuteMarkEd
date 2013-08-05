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
#ifndef HTMLHIGHLIGHTER_H
#define HTMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class HtmlHighlighter : public QSyntaxHighlighter
{
public:
    explicit HtmlHighlighter(QTextDocument *document);

    bool isEnabled() const;
    void setEnabled(bool enabled);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat *format;
    };
    QList<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat imageFormat;
    QTextCharFormat linkFormat;
    bool enabled;
};

#endif // HTMLHIGHLIGHTER_H
