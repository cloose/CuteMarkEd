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
