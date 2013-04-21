#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class HtmlPreviewGenerator;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();

    void editUndo();
    void editRedo();

    void styleDefault();
    void styleGithub();
    void styleClearness();
    void styleClearnessDark();

    void plainTextChanged();
    void htmlResultReady(const QString &html);

private:
    void setupActions();
    void setFileName(const QString &fileName);

    void load(const QString &fileName);

private:
    Ui::MainWindow *ui;
    HtmlPreviewGenerator* generator;
    QString         fileName;
};

#endif // MAINWINDOW_H
