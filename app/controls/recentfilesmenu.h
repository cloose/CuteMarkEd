#ifndef RECENTFILESMENU_H
#define RECENTFILESMENU_H

#include <QMenu>

class RecentFilesMenu : public QMenu
{
    Q_OBJECT
public:
    explicit RecentFilesMenu(QWidget *parent = 0);
    
    void readState();
    void saveState() const;

signals:
    void recentFileTriggered(const QString &fileName);

public slots:
    void addFile(const QString &fileName);
    void clearMenu();

private slots:
    void recentFileTriggered();

private:
    void updateMenu();

private:
    QStringList recentFiles;
};

#endif // RECENTFILESMENU_H
