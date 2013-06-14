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
#ifndef MARKDOWNMANIPULATOR_H
#define MARKDOWNMANIPULATOR_H

class QPlainTextEdit;
class QString;
class QChar;

class MarkdownManipulator
{
public:
    explicit MarkdownManipulator(QPlainTextEdit *editor);

    void wrapSelectedText(const QString &tag);
    void wrapCurrentParagraph(const QString &startTag, const QString &endTag);

    void appendToLine(const QString &text);
    void prependToLine(const QChar &mark);

    void increaseHeadingLevel();
    void decreaseHeadingLevel();

private:
    QPlainTextEdit *editor;
};

#endif // MARKDOWNMANIPULATOR_H
