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

    QFileInfo info(fileName);
    QString exportFileName = info.absoluteFilePath().replace(info.suffix(), "pdf");
    ui->exportToLineEdit->setText(exportFileName);

    // fill paper size combobox
    ui->paperSizeComboBox->addItem(tr("A4 (210 x 297 mm, 8.26 x 11.69 inches)"), QPrinter::A4);
    ui->paperSizeComboBox->addItem(tr("Letter (8.5 x 11 inches, 215.9 x 279.4 mm)"), QPrinter::Letter);
    ui->paperSizeComboBox->addItem(tr("Legal (8.5 x 14 inches, 215.9 x 355.6 mm)"), QPrinter::Legal);
    ui->paperSizeComboBox->addItem(tr("A5 (148 x 210 mm)"), QPrinter::A5);
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

void ExportPdfDialog::chooseFileButtonClicked()
{
    QString fileName = ui->exportToLineEdit->text();

    fileName = QFileDialog::getSaveFileName(this, tr("Export to PDF..."), fileName,
                                                  tr("PDF Files (*.pdf);;All Files (*)"));
    if (!fileName.isEmpty()) {
        ui->exportToLineEdit->setText(fileName);
    }
}
