/*
 * Copyright 2014 Christian Loose <christian.loose@hamburg.de>
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
#include "styledialog.h"
#include "ui_styledialog.h"

#include <styles/style.h>
#include <styles.h>


StyleDialog::StyleDialog(const QString &styleName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StyleDialog)
{
    ui->setupUi(this);

    Styles styles;
    ui->markdownHighlightingComboBox->addItems(styles.htmlPreviewStyleNames());
    ui->codeHighlightingComboBox->addItems(styles.codeHighlightings());
    ui->previewStylesheetComboBox->addItems(styles.previewStylesheets());

    if (!styleName.isEmpty()) {
        Style style = styles.style(styleName);
        ui->styleNameLineEdit->setText(styleName);
    }
}

StyleDialog::~StyleDialog()
{
    delete ui;
}

void StyleDialog::done(int result)
{
    if (result == QDialog::Accepted) {
    }

    QDialog::done(result);
}

