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
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

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
    void editCopyHtml();
    void editStrong();
    void editEmphasize();

    void viewChangeSplit();
    void styleDefault();
    void styleGithub();
    void styleSolarizedLight();
    void styleSolarizedDark();

    void helpAbout();

    void styleContextMenu(const QPoint &pos);
    void toggleHtmlView();

    void plainTextChanged();
    void htmlResultReady(const QString &html);
    void tocResultReady(const QString &toc);

    void tocLinkClicked(const QUrl &url);

    void splitterMoved(int pos, int index);

private:
    void setupActions();
    bool load(const QString &fileName);
    bool maybeSave();
    void setFileName(const QString &fileName);
    void updateSplitter(bool htmlViewToggled);

private:
    Ui::MainWindow *ui;
    QLabel *styleLabel;
    ActiveLabel *viewLabel;
    HtmlPreviewGenerator* generator;
    QString fileName;
    float splitFactor;
};

#endif // MAINWINDOW_H
