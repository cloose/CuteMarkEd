#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include <QFontComboBox>
#include <QSettings>

#include "options.h"

OptionsDialog::OptionsDialog(Options *opt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog),
    options(opt)
{
    ui->setupUi(this);
    ui->tabWidget->setTabIcon(0, QIcon("icon-file-text-alt.fontawesome"));
    ui->tabWidget->setIconSize(QSize(24, 24));

    ui->fontComboBox->setFontFilters(QFontComboBox::MonospacedFonts);

    foreach (int size, QFontDatabase::standardSizes()) {
        ui->sizeComboBox->addItem(QString().setNum(size));
    }

    QFont font = options->editorFont();
    ui->fontComboBox->setCurrentFont(font);
    ui->sizeComboBox->setCurrentText(QString().setNum(font.pointSize()));
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::done(int result)
{
    if (result == QDialog::Accepted) {
        QFont font = ui->fontComboBox->currentFont();
        font.setPointSize(ui->sizeComboBox->currentText().toInt());
        options->setEditorFont(font);
    }

    QDialog::done(result);
}
