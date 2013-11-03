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
#ifndef TABLETOOLDIALOG_H
#define TABLETOOLDIALOG_H

#include <QDialog>

#include <QList>
#include <QMap>

namespace Ui {
class TableToolDialog;
}
class QComboBox;
class QLineEdit;


class TableToolDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TableToolDialog(QWidget *parent = 0);
    ~TableToolDialog();
    
    int rows() const;
    int columns() const;

    QList<Qt::Alignment> alignments() const;
    QList<QStringList> tableCells() const;

private slots:
    void tableSizeChanged();

private:
    void addColumns(int newColumns);
    void removeColumns(int removedColumns);
    void addRows(int newRows);
    void removeRows(int removedRows);

    void updateTabOrder();

private:
    Ui::TableToolDialog *ui;
    int previousRowCount;
    int previousColumnCount;
    QList<QComboBox *> alignmentComboBoxList;
    QMap<QPoint, QLineEdit *> cellEditorMap;
};

#endif // TABLETOOLDIALOG_H
