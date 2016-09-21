#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <header/devicelist.h>

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
    void ShowCurrentTime() ;

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DeviceList * dList = NULL ;
};

#endif // MAINWINDOW_H
