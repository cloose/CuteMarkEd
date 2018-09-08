#ifndef FILEEXPLORERWIDGET_H
#define FILEEXPLORERWIDGET_H

#include <QWidget>
#include <QSet>
#include <QPersistentModelIndex>

namespace Ui {
class FileExplorerWidget;
}
class QFileSystemModel;
class QSortFilterProxyModel;


class FileExplorerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorerWidget(QWidget *parent = 0);
    ~FileExplorerWidget();

    void readState();
    void saveState() const;

signals:
    void fileSelected(const QString &filePath);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void fileExpanded(const QModelIndex &index);
    void fileCollapsed(const QModelIndex &index);
    void fileOpen(const QModelIndex &index);

private:
    bool initialized;
    Ui::FileExplorerWidget *ui;
    QFileSystemModel *model;
    QSortFilterProxyModel *sortModel;
    QSet<QPersistentModelIndex> m_expandedFolders;
    QPersistentModelIndex m_currentFile;
};

#endif // FILEEXPLORERWIDGET_H
