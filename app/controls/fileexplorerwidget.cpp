#include "fileexplorerwidget.h"
#include "ui_fileexplorerwidget.h"

#include <QFileSystemModel>
#include <QSortFilterProxyModel>

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
}

FileExplorerWidget::~FileExplorerWidget()
{
    delete ui;
}

void FileExplorerWidget::showEvent(QShowEvent *event)
{
    if (!initialized) {
        model->setRootPath("");
        initialized = true;
    }
    QWidget::showEvent(event);
}

void FileExplorerWidget::fileOpen(const QModelIndex &index)
{
    QFileInfo info = model->fileInfo(sortModel->mapToSource(index));
    if (info.isFile()) {
        const QString filePath = info.filePath();

        emit fileSelected(filePath);
    }
}
