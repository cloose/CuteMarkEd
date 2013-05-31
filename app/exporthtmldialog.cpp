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
