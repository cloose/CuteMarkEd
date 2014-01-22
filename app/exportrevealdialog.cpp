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
#include "exportrevealdialog.h"
#include "ui_exportrevealdialog.h"

#include <QFileDialog>
#include <QFileInfo>

ExportRevealDialog::ExportRevealDialog(const QString &fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportRevealDialog)
{
    ui->setupUi(this);

    // change button text of standard Ok button
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setText(tr("Export"));

    if (!fileName.isEmpty()) {
        QFileInfo info(fileName);
        ui->exportToLineEdit->setText(info.absolutePath()+"/presentation");
    }

    // initialize Ok button state
    exportToTextChanged(fileName);
}

ExportRevealDialog::~ExportRevealDialog()
{
    delete ui;
}

RevealOptions ExportRevealDialog::getRevealOptions()
{
    RevealOptions options;
    options.setAuthor(author());
    options.setDescription(description());
    options.setShowControls(showControls());
    options.setShowProgress(showProgress());
    options.setUseHistory(useHistory());
    options.setCenterPage(centerPage());
    return options;
}

QString ExportRevealDialog::pathName() const
{
    return ui->exportToLineEdit->text();
}

QString ExportRevealDialog::author() const
{
    return ui->authorLineEdit->text();
}

QString ExportRevealDialog::description() const
{
    return ui->descriptionTextEdit->toPlainText();
}

bool ExportRevealDialog::showControls() const
{
    return ui->showControlsCheckBox->isChecked();
}

bool ExportRevealDialog::showProgress() const
{
    return ui->showProgressCheckBox->isChecked();
}

bool ExportRevealDialog::useHistory() const
{
    return ui->useHistoryCheckBox->isChecked();
}

bool ExportRevealDialog::centerPage() const
{
    return ui->centerPageCheckBox->isChecked();
}

void ExportRevealDialog::exportToTextChanged(const QString &text)
{
    // only enable ok button if a filename was provided
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(!text.isEmpty());
}

void ExportRevealDialog::choosePathButtonClicked()
{
    QString pathName = ui->exportToLineEdit->text();

    pathName = QFileDialog::getExistingDirectory(this, tr("Export to reveal.js..."), pathName);
    if (!pathName.isEmpty()) {
        ui->exportToLineEdit->setText(pathName);
    }
}
