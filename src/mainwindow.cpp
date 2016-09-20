#include <header/mainwindow.h>
#include <header/devicelist.h>

#include <ui_mainwindow.h>
#include <iostream>
#include <QTimer>
#include <QFile>
#include <QDateTime>
#include <QTcpSocket>
#include <QDebug>

using namespace std ;

void MainWindow::ShowCurrentTime() {
    QDateTime time = QDateTime::currentDateTime() ;
    QString winTitle( "WIFI_tracker_MTK " ) ;
    winTitle += time.toString( "yyyy-MM-dd hh:mm:ss" ) ;
    this->setWindowTitle( winTitle );
} // ShowCurrentTime()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ShowCurrentTime();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ShowCurrentTime()));
    timer->start(1000); //time specified in ms

    QFile file("C:/Users/cyac/Repository/WIFI_tracker_MTK/metaData/testData.txt");
    file.open(QIODevice::ReadOnly);
    DeviceList * dList = new DeviceList( file.readAll() ) ;
    file.close();

    ui->treeView->setModel( dList ) ;

    cout << "hello YA!" << endl ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
