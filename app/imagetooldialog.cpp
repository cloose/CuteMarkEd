#include "imagetooldialog.h"
#include "ui_imagetooldialog.h"

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
