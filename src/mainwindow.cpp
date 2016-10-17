#include <header/mainwindow.h>
#include <header/tree/sorttreemodel.h>
#include <header/devicemap.h>
#include <header/globalvariable.h>
#include <header/client/machine.h>

#include <ui_mainwindow.h>
#include <iostream>
#include <Windows.h>
#include <QTimer>
#include <QFile>
#include <QDateTime>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

using namespace std ;

GlobalV Global;
void MainWindow::refreshDeviceList()
{
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    if ( list.size() > 0 )
    {
        //qDebug() << list[0].data().toString();
        deSelectAllMap();
        QString strIP = Global.deviceMap.getNodeIpByMac(list[0].data().toString());
        QList<Coordinate> coordList;
        Global.areaData.getNodeCoord(strIP, coordList);
        for( int i = 0; i < coordList.size(); i++ )
        {
            QModelIndex indexW = ui->tableWidget->model()->index(coordList[i].y, coordList[i].x);
            ui->tableWidget->selectionModel()->select(indexW, QItemSelectionModel::Select);
        } // for
    } // if
    /*QDirModel* model = (QDirModel*)ui->treeView->model();
    int row = -1;
    foreach (QModelIndex index, list)
    {
        if (index.row()!=row && index.column()==0)
        {
            QFileInfo fileInfo = model->fileInfo(index);
            qDebug() << fileInfo.fileName() << '\n';
            row = index.row();
        } // if
    } // foreach*/

    if ( Global.deviceMap.size() == 0 ) return;
        //static qint64 numOfData = 0;
        //qDebug() << gDeviceMap.getLast().toString() << endl;
        //dList->addData(gDeviceMap.getLast().toString());

    sView->update();
}

void MainWindow::refreshSelectedMap()
{

    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    if ( list.size() > 0 )
    {
        qDebug() << list[0].data().toString();
        deSelectAllMap();
        QList<Coordinate> coordList;
        Global.areaData.getNodeCoord(list[0].data().toString(), coordList);
        for( int i = 0; i < coordList.size(); i++ )
        {
            QModelIndex indexW = ui->tableWidget->model()->index(coordList[i].y, coordList[i].x);
            ui->tableWidget->selectionModel()->select(indexW, QItemSelectionModel::Select);
        } // for
    } // if

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

    Global.selectedNodeState = 0; // 閮剖?display??
    ui->setupUi(this);
    ShowCurrentTime();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ShowCurrentTime()));
    timer->start(1000); //time specified in ms

    QTimer *timer_DeviceRefresh = new QTimer(this);
    connect(timer_DeviceRefresh, SIGNAL(timeout()), this, SLOT(refreshDeviceList()));
    timer_DeviceRefresh->start(500); //time specified in ms

    //QFile file("./metaData/testData.txt");
    //file.open(QIODevice::ReadOnly);

    QStringList headers ;
    headers << "Device\'s MAC" << "Db" << "Frame" ;
    sView = new SortTreeView( ui->treeView, NULL, headers ) ; // file.readAll()
    sView->view->header()->resizeSection( 0, 130); // root column, size
    sView->view->header()->resizeSection( 1, 40);
    //file.close();

    Global.areaData.read("./metaData/AreaData_B207.JSON");
    QStringList headers_Node;
    headers_Node << "Ip" << "Location" << "Coordnate" ;
    nodeView = new SortTreeView( ui->treeView_2, Global.areaData.toString(), headers_Node ) ;
    nodeView->view->header()->resizeSection( 0, 200); // root column, size
    nodeView->view->header()->resizeSection( 1, 150); // root column, size

    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: gray;}"); // 閮剖??豢???憿
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(60);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(38);
    Global.areaData.getAllNodes(); //許蓋功
    Global.areaData.update2View(ui->tableWidget); // update node info to tablewidget
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

void MainWindow::selectMap(const QModelIndex index)
{

    int rows = index.model()->rowCount(index.parent()); // how many rows in this level
    //qDebug() << "rows is " << index.model()->index( 0,  0, index).data().toString();

    for ( int i = 0; i < rows; i++ )
    {
        //qDebug() << "rows is " << index.model()->index( i,  1, index.parent()).data().toString();
        QVariant vCoord = index.model()->index( i,  2, index.parent()).data();
        if  ( vCoord.isValid() )
        {

            QVariant vNodeIP = index.model()->index( i,  0, index.parent()).data() ;
            Global.deviceMap.setDisplayState(vNodeIP.toString(), Global.selectedNodeState);


            QString strCoord = vCoord.toString().remove(0,1);
            strCoord = strCoord.remove(strCoord.size()-1, strCoord.size());
            QList<QString> coordnate = strCoord.split("-");
            int x = coordnate.at(0).toInt();
            int y = coordnate.at(1).toInt();
            //qDebug() << x << y;
            //ui->tableWidget->setSelectionBehavior( QAbstractItemView::SelectItems );

            QModelIndex indexW = ui->tableWidget->model()->index(y, x);
            ui->tableWidget->selectionModel()->select(indexW, QItemSelectionModel::Select);
            //ui->tableWidget->setSelectionMode( QAbstractItemView::MultiSelection );
        } // if

        QModelIndex child = index.model()->index( 0,  0, index.model()->index( i,  0, index.parent()) );//.model()->index( i,  0, index);
        if ( child.isValid() )
            selectMap(child);
    } // for

}

 void MainWindow::deSelectAllMap()
 {
     for ( int i = 0; i < ui->tableWidget->rowCount(); i++ ) // deselect all
         for ( int j = 0; j < ui->tableWidget->columnCount(); j++ )
         {
             QModelIndex indexW = ui->tableWidget->model()->index(i, j);
             ui->tableWidget->selectionModel()->select(indexW, QItemSelectionModel::Deselect);
         } // for
 }

void MainWindow::on_treeView_2_clicked(const QModelIndex &index)
{
    //qDebug() << index.model()->index(index.row(),index.column() + 2, index).data(); // child data
    //qDebug() << index.model()->rowCount(index.parent());

    //if ( !index.child(0,0).isValid() )
    //    qDebug() << "no child";
    //ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection );

    deSelectAllMap();
    Global.selectedNodeState = Global.selectedNodeState > 99999 ? 0 : Global.selectedNodeState + 1; // 閮剖?displaystate?箏?撠??＊蝷?
    //qDebug() << "Global = " << Global.selectedNodeState;
    QVariant vCoord = index.model()->index( index.row(),  2, index.parent()).data() ;

    if  ( vCoord.isValid() )
    {

        QVariant vNodeIP = index.model()->index( index.row(),  0, index.parent()).data() ;
        Global.deviceMap.setDisplayState(vNodeIP.toString(), Global.selectedNodeState);

        QString strCoord = vCoord.toString().remove(0,1);
        strCoord = strCoord.remove(strCoord.size()-1, strCoord.size());
        QList<QString> coordnate = strCoord.split("-");
        int x = coordnate.at(0).toInt();
        int y = coordnate.at(1).toInt();
        //qDebug() << x << y;
        QModelIndex indexW = ui->tableWidget->model()->index(y, x);
        ui->tableWidget->selectionModel()->select(indexW, QItemSelectionModel::Select);
    } // if

    QModelIndex child = index.child(0,0);
    if ( child.isValid() )
        selectMap(child);
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    deSelectAllMap();
    static QModelIndex befIndex = index.model()->index(-1,-1);
    //qDebug() << index.row() << index.column();
    //qDebug() << befIndex.row() << befIndex.column();
    if (  befIndex.row() == index.row() )
    {

        /*ui->treeView->selectionModel()->select(index, QItemSelectionModel::Deselect);
        ui->treeView->selectionModel()->select(index.model()->index(index.row(), 1), QItemSelectionModel::Deselect);
        ui->treeView->selectionModel()->select(index.model()->index(index.row(), 2), QItemSelectionModel::Deselect);*/
        ui->treeView->setCurrentIndex(index.model()->index(-1,-1));
        befIndex = index.model()->index(-1,-1);
        //ui->treeView->clearFocus();
        return;
    } // if

    QString strIP = Global.deviceMap.getNodeIpByMac(index.model()->index(index.row(),0).data().toString());
    //qDebug() << "123" << strIP;
    befIndex = index;
    QList<Coordinate> coordList;
    Global.areaData.getNodeCoord(strIP, coordList);
    for( int i = 0; i < coordList.size(); i++ )
    {
        QModelIndex indexW = ui->tableWidget->model()->index(coordList[i].y, coordList[i].x);
        ui->tableWidget->selectionModel()->select(indexW, QItemSelectionModel::Select);
    } // for
        //qDebug() << coordList[i].x << coordList[i].y;

}

void MainWindow::on_actionNew_window_triggered()
{
    camView * ww = new camView( "http://192.168.1.4:8080", NULL ) ;
    ww->show();
}
