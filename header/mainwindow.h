#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <header/sorttreemodel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots :
    void refreshDeviceList();
    void ShowCurrentTime() ;

    void on_pushButton_clicked();

    void on_debug_remove_triggered();

    void on_debug_edit_triggered();

private:
    Ui::MainWindow *ui;
    SortTreeView * sView = NULL ;
};

#endif // MAINWINDOW_H
