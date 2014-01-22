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
#ifndef REVEALOPTIONS_H
#define REVEALOPTIONS_H
#include <QString>
#include <QObject>

class RevealOptions
{
public:
    QString author() const;
    void setAuthor(const QString& author);
    QString description() const;
    void setDescription(const QString& description);
    bool showControls() const;
    void setShowControls(bool on);
    bool showProgress() const;
    void setShowProgress(bool on);
    bool useHistory() const;
    void setUseHistory(bool on);
    bool centerPage() const;
    void setCenterPage(bool on);
private:
    QString m_author;
    QString m_description;
    bool m_showControls;
    bool m_showProgress;
    bool m_useHistory;
    bool m_centerPage;
};

#endif // REVEALOPTIONS_H
