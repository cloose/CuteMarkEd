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
#include "exportpdfdialog.h"
#include "ui_exportpdfdialog.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QPrinter>

ExportPdfDialog::ExportPdfDialog(const QString &fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportPdfDialog)
{
    ui->setupUi(this);

    // change button text of standard Ok button
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setText("Export PDF");

    if (!fileName.isEmpty()) {
        QFileInfo info(fileName);
        QString exportFileName = info.absoluteFilePath().replace(info.suffix(), "pdf");
        ui->exportToLineEdit->setText(exportFileName);
    }

    // fill paper size combobox
    ui->paperSizeComboBox->addItem(tr("A4 (210 x 297 mm, 8.26 x 11.69 inches)"), QPrinter::A4);
    ui->paperSizeComboBox->addItem(tr("Letter (8.5 x 11 inches, 215.9 x 279.4 mm)"), QPrinter::Letter);
    ui->paperSizeComboBox->addItem(tr("Legal (8.5 x 14 inches, 215.9 x 355.6 mm)"), QPrinter::Legal);
    ui->paperSizeComboBox->addItem(tr("A3 (297 x 420 mm)"), QPrinter::A3);
    ui->paperSizeComboBox->addItem(tr("A5 (148 x 210 mm)"), QPrinter::A5);
    ui->paperSizeComboBox->addItem(tr("A6 (105 x 148 mm)"), QPrinter::A6);
    ui->paperSizeComboBox->addItem(tr("B4 (250 x 353 mm)"), QPrinter::B4);
    ui->paperSizeComboBox->addItem(tr("B5 (176 x 250 mm, 6.93 x 9.84 inches)"), QPrinter::B5);

    // initialize Ok button state
    exportToTextChanged(fileName);
}

ExportPdfDialog::~ExportPdfDialog()
{
    delete ui;
}

QPrinter *ExportPdfDialog::printer()
{
    QString fileName = ui->exportToLineEdit->text();

    QPrinter::Orientation orientation;
    if (ui->portraitRadioButton->isChecked()) {
        orientation = QPrinter::Portrait;
    } else {
        orientation = QPrinter::Landscape;
    }

    QVariant v = ui->paperSizeComboBox->itemData(ui->paperSizeComboBox->currentIndex());
    QPrinter::PaperSize size = (QPrinter::PaperSize)v.toInt();

    QPrinter *p = new QPrinter();
    p->setOutputFileName(fileName);
    p->setOutputFormat(QPrinter::PdfFormat);
    p->setOrientation(orientation);
    p->setPaperSize(size);

    return p;
}

void ExportPdfDialog::exportToTextChanged(const QString &text)
{
    // only enable ok button if a filename was provided
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(!text.isEmpty());
}

void ExportPdfDialog::chooseFileButtonClicked()
{
    QString fileName = ui->exportToLineEdit->text();

    fileName = QFileDialog::getSaveFileName(this, tr("Export to PDF..."), fileName,
                                                  tr("PDF Files (*.pdf);;All Files (*)"));
    if (!fileName.isEmpty()) {
        ui->exportToLineEdit->setText(fileName);
    }
}
