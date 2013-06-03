#ifndef EXPORTPDFDIALOG_H
#define EXPORTPDFDIALOG_H

#include <QDialog>

namespace Ui {
class ExportPdfDialog;
}
class QPrinter;

class ExportPdfDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportPdfDialog(const QString &fileName, QWidget *parent = 0);
    ~ExportPdfDialog();
    
    QPrinter *printer();

private slots:
    void exportToTextChanged(const QString &text);
    void chooseFileButtonClicked();

private:
    Ui::ExportPdfDialog *ui;
};

#endif // EXPORTPDFDIALOG_H
