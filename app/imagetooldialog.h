#ifndef IMAGETOOLDIALOG_H
#define IMAGETOOLDIALOG_H

#include <QDialog>

namespace Ui {
class ImageToolDialog;
}

class ImageToolDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImageToolDialog(QWidget *parent = 0);
    ~ImageToolDialog();
    
private:
    Ui::ImageToolDialog *ui;
};

#endif // IMAGETOOLDIALOG_H
