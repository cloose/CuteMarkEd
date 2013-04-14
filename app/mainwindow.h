#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MarkdownParser;


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

    void styleChanged(const QString &itemText);

private:
    void setupActions();
    void setFileName(const QString &fileName);

    void load(const QString &fileName);

private:
    Ui::MainWindow *ui;
    MarkdownParser *parser;
    QString         fileName;
};

#endif // MAINWINDOW_H
