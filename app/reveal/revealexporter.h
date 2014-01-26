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
#ifndef REVEALEXPORTER_H
#define REVEALEXPORTER_H
#include <QString>

class RevealOptions;
class QStringList;

class RevealExporter
{
public:
    RevealExporter(const QString& text);
    void run(const QString& destPath, const RevealOptions& revealOptions);
private:
    QString generateOutput(const QString& indexHtml, const QString& title, const QStringList& pages, const RevealOptions& revealOptions);
    QString readIndexHtml();
    QString writeIndexHtml(const QString& destPath, const QString& content);
    QString extractTitle();
    QStringList extractPages();
private:
    QString code;
};

#endif // REVEALEXPORTER_H
