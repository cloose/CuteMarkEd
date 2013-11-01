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
#include "exporthtmldialog.h"
#include "ui_exporthtmldialog.h"

#include <QFileDialog>
#include <QFileInfo>

ExportHtmlDialog::ExportHtmlDialog(const QString &fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportHtmlDialog)
{
    ui->setupUi(this);

    // change button text of standard Ok button
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setText("Export HTML");

    if (!fileName.isEmpty()) {
        QFileInfo info(fileName);
        QString exportFileName = info.absoluteFilePath().replace(info.suffix(), "html");
        ui->exportToLineEdit->setText(exportFileName);
    }

    // initialize Ok button state
    exportToTextChanged(fileName);
}

ExportHtmlDialog::~ExportHtmlDialog()
{
    delete ui;
}

QString ExportHtmlDialog::fileName() const
{
    return ui->exportToLineEdit->text();
}

bool ExportHtmlDialog::includeCSS() const
{
    return ui->styleCheckBox->isChecked();
}

bool ExportHtmlDialog::includeCodeHighlighting() const
{
    return ui->highlightCheckBox->isChecked();
}

void ExportHtmlDialog::exportToTextChanged(const QString &text)
{
    // only enable ok button if a filename was provided
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(!text.isEmpty());
}

void ExportHtmlDialog::chooseFileButtonClicked()
{
    QString fileName = ui->exportToLineEdit->text();

    fileName = QFileDialog::getSaveFileName(this, tr("Export to HTML..."), fileName,
                                                  tr("HTML Files (*.html *.htm);;All Files (*)"));
    if (!fileName.isEmpty()) {
        ui->exportToLineEdit->setText(fileName);
    }
}
