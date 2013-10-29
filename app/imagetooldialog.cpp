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
#include "imagetooldialog.h"
#include "ui_imagetooldialog.h"

#include <QFileDialog>
#include <QUrl>

ImageToolDialog::ImageToolDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageToolDialog)
{
    ui->setupUi(this);
}

ImageToolDialog::~ImageToolDialog()
{
    delete ui;
}

QString ImageToolDialog::alternateText() const
{
    return ui->alternateTextEdit->text();
}

QString ImageToolDialog::imageSourceLink() const
{
    return ui->imageLinkEdit->text();
}

QString ImageToolDialog::optionalTitle() const
{
    return ui->optionalTitleEdit->text();
}

void ImageToolDialog::chooseFileButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QString(),
                                                    tr("Images (*.bmp *.gif *.jpg *.jpe *.jpeg *.png *.tif *.tiff *.xpm);;All Files (*)"));
    if (!fileName.isEmpty()) {
        ui->imageLinkEdit->setText(QUrl::fromLocalFile(fileName).toDisplayString());
    }
}
