#include <header/mainwindow.h>
#include <header/sorttreemodel.h>
#include <header/devicemap.h>

#include <ui_mainwindow.h>
#include <iostream>
#include <Windows.h>
#include <QTimer>
#include <QFile>
#include <QDateTime>
#include <QTcpSocket>
#include <QDebug>

using namespace std ;

DeviceMap gDeviceMap;
void MainWindow::refreshDeviceList()
{
    if ( gDeviceMap.size() == 0 ) return;
        //static qint64 numOfData = 0;
        //qDebug() << gDeviceMap.getLast().toString() << endl;
        //dList->addData(gDeviceMap.getLast().toString());
    sView->update();

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

    QTimer *timer_DeviceRefresh = new QTimer(this);
    connect(timer_DeviceRefresh, SIGNAL(timeout()), this, SLOT(refreshDeviceList()));
    timer_DeviceRefresh->start(1000); //time specified in ms

    QFile file("./metaData/testData.txt");
    file.open(QIODevice::ReadOnly);

    QStringList headers ;

    headers << "Device\'s MAC" << "Db" ;
    sView = new SortTreeView( ui->treeView, file.readAll(), headers ) ;
    file.close();

    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(38);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(38);
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

    sView->model->setFilterRegExp(QRegExp( regExp.join( "" ) ));
    sView->model->setFilterKeyColumn( ui->comboBox->currentIndex() );
}

void MainWindow::on_debug_remove_triggered()
{
   sView->searchRemove( ui->searchTarget->text() );
}

void MainWindow::on_debug_edit_triggered()
{
   sView->searchEdit( ui->searchTarget->text() );
}
