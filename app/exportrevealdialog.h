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
#ifndef EXPORTREVEALDIALOG_H
#define EXPORTREVEALDIALOG_H

#include <QDialog>
#include "reveal/revealoptions.h"

namespace Ui {
class ExportRevealDialog;
}
class QPrinter;

class ExportRevealDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportRevealDialog(const QString &fileName, QWidget *parent = 0);
    ~ExportRevealDialog();

    RevealOptions getRevealOptions();
    
    QString pathName() const;
    QString author() const;
    QString description() const;
    bool showControls() const;
    bool showProgress() const;
    bool useHistory() const;
    bool centerPage() const;

private slots:
    void exportToTextChanged(const QString &text);
    void choosePathButtonClicked();

private:
    Ui::ExportRevealDialog *ui;
};

#endif // EXPORTREVEALDIALOG_H
