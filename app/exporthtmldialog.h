#ifndef EXPORTHTMLDIALOG_H
#define EXPORTHTMLDIALOG_H

#include <QDialog>

namespace Ui {
class ExportHtmlDialog;
}
class QPrinter;

class ExportHtmlDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportHtmlDialog(const QString &fileName, QWidget *parent = 0);
    ~ExportHtmlDialog();
    
    QString fileName() const;
    bool includeCSS() const;

private slots:
    void exportToTextChanged(const QString &text);
    void chooseFileButtonClicked();

private:
    Ui::ExportHtmlDialog *ui;
};

#endif // EXPORTHTMLDIALOG_H
