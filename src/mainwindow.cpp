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
