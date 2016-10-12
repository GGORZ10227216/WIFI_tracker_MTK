#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <header/tree/sorttreemodel.h>

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
    void refreshSelectedMap();
    void deSelectAllMap();
    void selectMap(const QModelIndex index);

    void refreshDeviceList();
    void ShowCurrentTime() ;

    void on_pushButton_clicked();

    void on_debug_remove_triggered();

    void on_debug_edit_triggered();

    void on_treeView_2_clicked(const QModelIndex &index);

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    SortTreeView * sView = NULL ;
    SortTreeView * nodeView = NULL ;
};

#endif // MAINWINDOW_H
