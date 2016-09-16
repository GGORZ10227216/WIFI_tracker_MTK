#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cout << "hello world" << endl ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
