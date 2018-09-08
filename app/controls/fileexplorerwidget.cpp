#include "fileexplorerwidget.h"
#include "ui_fileexplorerwidget.h"

#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QSettings>

class FileSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    FileSortFilterProxyModel(QObject *parent = 0) : QSortFilterProxyModel(parent) {}

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const
    {
        QFileSystemModel *model = static_cast<QFileSystemModel*>(this->sourceModel());

        QFileInfo leftInfo  = model->fileInfo(left);
        QFileInfo rightInfo = model->fileInfo(right);

        if (leftInfo.isDir() == rightInfo.isDir())
            return (leftInfo.filePath().compare(rightInfo.filePath(), Qt::CaseInsensitive) < 0);

        return leftInfo.isDir();
    }
};


FileExplorerWidget::FileExplorerWidget(QWidget *parent) :
    QWidget(parent),
    initialized(false),
    ui(new Ui::FileExplorerWidget),
    model(new QFileSystemModel(this)),
    sortModel(new FileSortFilterProxyModel(this))
{
    ui->setupUi(this);

    sortModel->setDynamicSortFilter(true);
    sortModel->setSourceModel(model);

    ui->fileTreeView->setModel(sortModel);
    ui->fileTreeView->hideColumn(1);
    ui->fileTreeView->sortByColumn(0, Qt::AscendingOrder);

    connect(ui->fileTreeView, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(fileOpen(QModelIndex)));
    connect(ui->fileTreeView, SIGNAL(expanded(QModelIndex)),
            SLOT(fileExpanded(QModelIndex)));
    connect(ui->fileTreeView, SIGNAL(collapsed(QModelIndex)),
            SLOT(fileCollapsed(QModelIndex)));
}

FileExplorerWidget::~FileExplorerWidget()
{
    delete ui;
}

void FileExplorerWidget::readState()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("fileExplorer"));

    ui->fileTreeView->header()->restoreState(settings.value(QStringLiteral("headerState")).toByteArray());

    const QString currentFile(settings.value(QStringLiteral("currentFile")).toString());
    const QStringList expandedFolders(settings.value(QStringLiteral("expandedFolders")).toStringList());

    foreach (const QString &folder, expandedFolders) {
        const QModelIndex sourceIndex(model->index(folder));
        if (sourceIndex.isValid()) {
            const QModelIndex proxyIndex(sortModel->mapFromSource(sourceIndex));
            ui->fileTreeView->expand(proxyIndex);
        }
    }

    if (!currentFile.isEmpty()) {
        const QModelIndex sourceIndex(model->index(currentFile));
        if (sourceIndex.isValid()) {
            const QModelIndex proxyIndex(sortModel->mapFromSource(sourceIndex));
            ui->fileTreeView->setCurrentIndex(proxyIndex);
            fileOpen(proxyIndex);
        }
    }
}

void FileExplorerWidget::saveState() const
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("fileExplorer"));

    settings.setValue(QStringLiteral("headerState"), ui->fileTreeView->header()->saveState());

    settings.setValue(QStringLiteral("currentFile"), model->filePath(m_currentFile));

    QStringList folders;
    foreach (const QPersistentModelIndex &folder, m_expandedFolders) {
        folders << model->filePath(folder);
    }
    settings.setValue(QStringLiteral("expandedFolders"), folders);
}

void FileExplorerWidget::showEvent(QShowEvent *event)
{
    if (!initialized) {
        model->setRootPath("");
        initialized = true;
    }
    QWidget::showEvent(event);
}

void FileExplorerWidget::fileExpanded(const QModelIndex &index)
{
    m_expandedFolders.insert(sortModel->mapToSource(index));
}

void FileExplorerWidget::fileCollapsed(const QModelIndex &index)
{
    m_expandedFolders.remove(sortModel->mapToSource(index));
}

void FileExplorerWidget::fileOpen(const QModelIndex &index)
{
    const QModelIndex sourceIndex(sortModel->mapToSource(index));
    QFileInfo info = model->fileInfo(sourceIndex);
    if (info.isFile()) {
        const QString filePath = info.filePath();
        m_currentFile = sourceIndex;
        emit fileSelected(filePath);
    }
}
