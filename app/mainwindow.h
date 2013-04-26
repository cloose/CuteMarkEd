#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QLabel;
class ActiveLabel;
class HtmlPreviewGenerator;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;

private slots:
    void initializeUI();

    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void fileExportToHtml();
    void fileExportToPdf();

    void editUndo();
    void editRedo();

    void styleDefault();
    void styleGithub();
    void styleSolarizedLight();
    void styleSolarizedDark();

    void helpAbout();

    void styleContextMenu(const QPoint &pos);
    void toggleHtmlView();

    void plainTextChanged();
    void htmlResultReady(const QString &html);

private:
    void setupActions();
    bool load(const QString &fileName);
    bool maybeSave();
    void setFileName(const QString &fileName);


private:
    Ui::MainWindow *ui;
    QLabel *styleLabel;
    ActiveLabel *viewLabel;
    HtmlPreviewGenerator* generator;
    QString fileName;
};

#endif // MAINWINDOW_H
