#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}
class Options;

class OptionsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OptionsDialog(Options *opt, QWidget *parent = 0);
    ~OptionsDialog();

protected:
    void done(int result);

private:
    Ui::OptionsDialog *ui;
    Options *options;
};

#endif // OPTIONSDIALOG_H
