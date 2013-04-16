#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace Discount {
class Document;
}


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

private:
    void setupActions();
    void setFileName(const QString &fileName);

    void load(const QString &fileName);

private:
    Ui::MainWindow *ui;
    Discount::Document *document;
    QString         fileName;
};

#endif // MAINWINDOW_H
