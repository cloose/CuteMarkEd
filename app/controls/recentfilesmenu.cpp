#include "recentfilesmenu.h"

#include <QFileInfo>
#include <QSettings>

RecentFilesMenu::RecentFilesMenu(QWidget *parent) :
    QMenu(tr("Recent &Files"), parent)
{
}

void RecentFilesMenu::readState()
{
    QSettings settings;

    int size = settings.beginReadArray("recentFiles");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        recentFiles << settings.value("fileName").toString();
    }
    settings.endArray();

    updateMenu();
}

void RecentFilesMenu::saveState() const
{
    QSettings settings;

    settings.beginWriteArray("recentFiles");
    for (int i = 0; i < recentFiles.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("fileName", recentFiles.at(i));
    }
    settings.endArray();
}

void RecentFilesMenu::addFile(const QString &fileName)
{
    // add file to top of list
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);

    if (recentFiles.size() > 10) {
        recentFiles.removeLast();
    }

    updateMenu();
}

void RecentFilesMenu::clearMenu()
{
    recentFiles.clear();
    updateMenu();
}

void RecentFilesMenu::recentFileTriggered()
{
    QAction *action = qobject_cast<QAction*>(sender());
    emit recentFileTriggered(action->data().toString());
}

void RecentFilesMenu::updateMenu()
{
    clear();

    foreach (const QString &recentFile, recentFiles) {
        QAction *action = addAction(recentFile);
        action->setData(recentFile);

        connect(action, SIGNAL(triggered()),
                this, SLOT(recentFileTriggered()));
    }

    addSeparator();
    addAction(tr("Clear Menu"), this, SLOT(clearMenu()));

    setEnabled(!recentFiles.empty());
}
