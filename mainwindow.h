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

    void plainTextChanged();

private:
    Ui::MainWindow *ui;
    MarkdownParser *parser;
};

#endif // MAINWINDOW_H
