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

#include <QPushButton>

#include <styles/style.h>
#include <styles.h>


StyleDialog::StyleDialog(DialogMode mode, const QString &styleName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StyleDialog),
    styles(new Styles()),
    dialogMode(mode)
{
    ui->setupUi(this);

    ui->markdownHighlightingComboBox->addItems(styles->markdownHighlightings());
    ui->codeHighlightingComboBox->addItems(styles->codeHighlightings());
    ui->previewStylesheetComboBox->addItems(styles->previewStylesheets());

    if (!styleName.isEmpty()) {
        Style style = styles->style(styleName);
        ui->styleNameLineEdit->setText(styleName);
        ui->markdownHighlightingComboBox->setCurrentText(style.markdownHighlighting);
        ui->codeHighlightingComboBox->setCurrentText(style.codeHighlighting);
        ui->previewStylesheetComboBox->setCurrentText(style.previewStylesheet);
    }

    updateOkButtonEnabledState();
}

StyleDialog::~StyleDialog()
{
    delete styles;
    delete ui;
}

void StyleDialog::done(int result)
{
    if (result == QDialog::Accepted) {
        switch (dialogMode)
        {
            case AddMode:
                addNewStyle();
                break;

            case EditMode:
                updateStyle();
                break;

            case RemoveMode:
                removeStyle();
                break;
        }
    }

    QDialog::done(result);
}

void StyleDialog::updateOkButtonEnabledState()
{
    QString styleName = ui->styleNameLineEdit->text();

    bool isNameFilled = !styleName.isEmpty();
    bool nameDoesNotExists = dialogMode != AddMode || !styles->htmlPreviewStyleNames().contains(styleName);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(isNameFilled && nameDoesNotExists);
}

void StyleDialog::addNewStyle()
{
    Style newStyle;
    newStyle.name = ui->styleNameLineEdit->text();
    newStyle.markdownHighlighting = ui->markdownHighlightingComboBox->currentText();
    newStyle.codeHighlighting = ui->codeHighlightingComboBox->currentText();
    newStyle.previewStylesheet = ui->previewStylesheetComboBox->currentText();

    styles->addHtmlPreviewStyle(newStyle);
}

void StyleDialog::updateStyle()
{
    Style style = styles->style(ui->styleNameLineEdit->text());
    style.markdownHighlighting = ui->markdownHighlightingComboBox->currentText();
    style.codeHighlighting = ui->codeHighlightingComboBox->currentText();
    style.previewStylesheet = ui->previewStylesheetComboBox->currentText();

    styles->updateHtmlPreviewStyle(style);
}

void StyleDialog::removeStyle()
{
    styles->removeHtmlPreviewStyle(ui->styleNameLineEdit->text());
}
