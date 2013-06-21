#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include <QFontComboBox>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    ui->tabWidget->setTabIcon(0, QIcon("icon-file-text-alt.fontawesome"));
    ui->tabWidget->setIconSize(QSize(24, 24));

    ui->fontComboBox->setFontFilters(QFontComboBox::MonospacedFonts);

    foreach (int size, QFontDatabase::standardSizes()) {
        ui->sizeComboBox->addItem(QString().setNum(size));
    }
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::on_fontComboBox_currentFontChanged(const QFont &f)
{
}
