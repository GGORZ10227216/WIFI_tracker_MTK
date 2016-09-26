#include <header/mainwindow.h>
#include <header/devicelist.h>
#include <header/devicedata.h>
#include <header/devicemap.h>

#include <ui_mainwindow.h>
#include <iostream>
#include <Windows.h>
#include <QTimer>
#include <QFile>
#include <QDateTime>
#include <QTcpSocket>
#include <QDebug>

DeviceMap gDeviceMap;
using namespace std ;

void MainWindow::refreshDeviceList()
{

}

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

    // set timer to refresh devicelist
    QTimer *timer_DeviceList = new QTimer(this);
    connect(timer_DeviceList, SIGNAL(timeout()), this, SLOT(refreshDeviceList()));
    timer_DeviceList->start(1000); //time specified in ms

    QFile file("./metaData/testData.txt");
    file.open(QIODevice::ReadOnly);
    dList = new DeviceList( file.readAll(), ui->treeView ) ;
    file.close();

    cout << "hello YA!" << endl ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString sTarget = ui->searchTarget->text() ;
    QStringList regExp ;

    regExp << ".*" << sTarget << ".*" ;
    qDebug() << regExp.join( "" ) ;

    dList->qSftm->setFilterRegExp(QRegExp( regExp.join( "" ) ));
    dList->qSftm->setFilterKeyColumn(1);
}

void MainWindow::on_action555_triggered()
{
    // MessageBox(NULL, L"Hello", L"box", MB_OK);
    //cout << "messagebox" << endl;
   // cout << dList->index(1, 1, dList->rootItem)->;
    dList->insertRow(0);

}
