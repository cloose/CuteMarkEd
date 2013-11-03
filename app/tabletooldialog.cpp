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
#include "tabletooldialog.h"
#include "ui_tabletooldialog.h"

#include <QComboBox>
#include <QLineEdit>

// Make QPoint in QMap work
bool operator<(const QPoint& lhs, const QPoint& rhs)
{
    if (lhs.x() < rhs.x())
        return true;
    else if (lhs.x() == rhs.x())
        return lhs.y() < rhs.y();
    else
        return false;
}

TableToolDialog::TableToolDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableToolDialog),
    previousRowCount(0),
    previousColumnCount(0)
{
    ui->setupUi(this);
    tableSizeChanged();
}

TableToolDialog::~TableToolDialog()
{
    delete ui;
}

int TableToolDialog::rows() const
{
    return ui->rowsSpinBox->value();
}

int TableToolDialog::columns() const
{
    return ui->columnsSpinBox->value();
}

QList<Qt::Alignment> TableToolDialog::alignments() const
{
    QList<Qt::Alignment> alignments;

    foreach (QComboBox *cb, alignmentComboBoxList) {
        Qt::Alignment alignment = (Qt::Alignment)cb->itemData(cb->currentIndex()).toInt();
        alignments.append(alignment);
    }

    return alignments;
}

QList<QStringList> TableToolDialog::tableCells() const
{
    QList<QStringList> table;

    for (int row = 0; row < rows(); ++row) {
        QStringList rowData;

        for (int col = 0; col < columns(); ++col) {
            rowData << cellEditorMap[QPoint(col, row)]->text();
        }

        table.append(rowData);
    }

    return table;
}

void TableToolDialog::tableSizeChanged()
{
    int rowDiff = rows() - previousRowCount;
    int columnDiff = columns() - previousColumnCount;

    if (columnDiff > 0) {
        addColumns(columnDiff);
    } else if (columnDiff < 0) {
        removeColumns(columnDiff);
    } else if (rowDiff > 0) {
        addRows(rowDiff);
    } else if (rowDiff < 0) {
        removeRows(rowDiff);
    }

    updateTabOrder();

    previousColumnCount = columns();
    previousRowCount = rows();
}

void TableToolDialog::addColumns(int newColumns)
{
    for (int col = 0; col < newColumns; ++col) {
        // add combo box to choose alignment of column
        QComboBox *cb = new QComboBox(ui->tableGroupBox);
        cb->addItem(tr("Left"), Qt::AlignLeft);
        cb->addItem(tr("Center"), Qt::AlignCenter);
        cb->addItem(tr("Right"), Qt::AlignRight);
        ui->tableGridLayout->addWidget(cb, 0, col+previousColumnCount+1);

        alignmentComboBoxList << cb;

        // add a column of new line edits
        for (int row = 0; row < rows(); ++row) {
            QLineEdit *edit = new QLineEdit(ui->tableGroupBox);
            ui->tableGridLayout->addWidget(edit, row+1, col+previousColumnCount+1);

            cellEditorMap.insert(QPoint(col+previousColumnCount, row), edit);
        }
    }
}

void TableToolDialog::removeColumns(int removedColumns)
{
    for (int col = 0; col < qAbs(removedColumns); ++col) {
        // remove alignment combo box in last column
        QComboBox *cb = alignmentComboBoxList.last();

        alignmentComboBoxList.removeLast();
        ui->tableGridLayout->removeWidget(cb);

        cb->deleteLater();

        // remove all line edits in last column
        for (int row = 0; row < rows(); ++row) {
            QLineEdit *edit = cellEditorMap[QPoint(previousColumnCount-col-1, row)];

            cellEditorMap.remove(QPoint(previousColumnCount-col-1, row));
            ui->tableGridLayout->removeWidget(edit);

            edit->deleteLater();
        }
    }
}

void TableToolDialog::addRows(int newRows)
{
    for (int row = 0; row < newRows; ++row) {
        // add a new row of line edits
        for (int col = 0; col < columns(); ++col) {
            QLineEdit *edit = new QLineEdit(ui->tableGroupBox);
            ui->tableGridLayout->addWidget(edit, row+previousRowCount+1, col+1);

            cellEditorMap.insert(QPoint(col, row+previousRowCount), edit);
        }
    }
}

void TableToolDialog::removeRows(int removedRows)
{
    for (int row = 0; row < qAbs(removedRows); ++row) {
        // remove all line edits in current row
        for (int col = 0; col < columns(); ++col) {
            QLineEdit *edit = cellEditorMap[QPoint(col, previousRowCount-row-1)];

            cellEditorMap.remove(QPoint(col, previousRowCount-row-1));
            ui->tableGridLayout->removeWidget(edit);

            edit->deleteLater();
        }
    }
}

void TableToolDialog::updateTabOrder()
{
    // tab between spin boxes
    this->setTabOrder(ui->rowsSpinBox, ui->columnsSpinBox);

    QWidget *first = ui->columnsSpinBox;
    foreach (QComboBox *cb, alignmentComboBoxList) {
        this->setTabOrder(first, cb);
        first = cb;
    }

    // tab between line edits from left-to-right
    for (int row = 0; row < rows(); ++row) {
        for (int col = 0; col < columns(); ++col) {
            this->setTabOrder(first, cellEditorMap[QPoint(col, row)]);
            first = cellEditorMap[QPoint(col, row)];
        }
    }

    // tab between last line edit and okay button
    this->setTabOrder(first, ui->buttonBox);
}
