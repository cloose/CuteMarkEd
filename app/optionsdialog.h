#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();
    
private slots:
    void on_fontComboBox_currentFontChanged(const QFont &f);

private:
    Ui::OptionsDialog *ui;
};

#endif // OPTIONSDIALOG_H
