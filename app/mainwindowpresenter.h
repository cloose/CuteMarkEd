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
#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include <QObject>

class IMainWindow;
class HtmlPreviewGenerator;
class Options;


class MainWindowPresenter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

public:
    MainWindowPresenter(QObject *view, Options *options);
    ~MainWindowPresenter();
    
    void onViewReady();

    QString fileName() const;
    void setFileName(const QString &fileName);

    QUrl previewBaseUrl() const;

signals:
    void fileNameChanged(const QString &fileName);

public slots:
    bool loadFile(const QString &fileName);

    void setMathSupportEnabled(bool enabled);
    void setCodeHighlightingEnabled(bool enabled);
    void setCodeHighlightingStyle(const QString &style);

private:
    IMainWindow *view;
    HtmlPreviewGenerator *generator;
    QString m_fileName;
};

#endif // MAINWINDOWPRESENTER_H
