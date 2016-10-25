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
#include <QFileDialog>

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

    //qDebug() << "--------------------------" << Global.deviceMap.size();
    if ( Global.deviceMap.size() == 0 ) return;
        //static qint64 numOfData = 0;
        //qDebug() << gDeviceMap.getLast().toString() << endl;
        //dList->addData(gDeviceMap.getLast().toString());
    //this->ui->treeView->model()->removeRows(0, this->ui->treeView->model()->rowCount());
    sView->update(Global.strKeyword);
    //Global.updateNewestNumber = ++Global.updateNewestNumber % 1000;
    //Global.deviceMap.clear();
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

void MainWindow::reConnectServer()
{
    if ( Global.needReConnect.size() <= 0 ) return;

    foreach ( Server s, Global.needReConnect )
        Global.n_mana.connectSever(s.strIp, 48763, s.strMac, s.intChannel );
    Global.needReConnect.clear();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    Global.selectedNodeState = 0; // 閮剖?display??
    Global.updateNewestNumber = 0;
    ui->setupUi(this);
    ShowCurrentTime();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ShowCurrentTime()));
    timer->start(500); //time specified in ms

    QTimer *timer_DeviceRefresh = new QTimer(this);
    connect(timer_DeviceRefresh, SIGNAL(timeout()), this, SLOT(refreshDeviceList()));
    timer_DeviceRefresh->start(1000); //time specified in ms

    QTimer *timer_Reconnect = new QTimer(this);
    connect(timer_Reconnect, SIGNAL(timeout()), this, SLOT(reConnectServer()));
    timer_Reconnect->start(10000); //time specified in ms
    //QFile file("./metaData/testData.txt");
    //file.open(QIODevice::ReadOnly);

    QStringList headers ;
    headers << "Device\'s MAC" << "Db" << "Frame" ;
    sView = new SortTreeView( ui->treeView, NULL, headers ) ; // file.readAll()
    sView->view->header()->resizeSection( 0, 130); // root column, size
    sView->view->header()->resizeSection( 1, 40);
    //file.close();


    QStringList headers_Node;
    headers_Node << "Ip" << "Location" << "Coordnate" ;
    nodeView = new SortTreeView( ui->treeView_2, NULL, headers_Node ) ;
    nodeView->view->header()->resizeSection( 0, 200); // root column, size
    nodeView->view->header()->resizeSection( 1, 150); // root column, size

    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: gray;}"); // 閮剖??豢???憿
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(60);
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
    Global.strKeyword = sTarget;
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

    if  ( vCoord.isValid() ) {

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
    static QModelIndex befIndex = index.model()->index(-1,-1) ;
    if ( befIndex.row() == index.row() ) {
        ui->treeView->setCurrentIndex(index.model()->index(-1,-1));
        befIndex = index.model()->index(-1,-1);
        return;
    } // if

     //qDebug() << "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFUCK";
    QString strIP = Global.deviceMap.getNodeIpByMac(index.model()->index(index.row(),0).data().toString());
    befIndex = index;
    QList<Coordinate> coordList;
    Global.areaData.getNodeCoord(strIP, coordList);
    for( int i = 0; i < coordList.size(); i++ ) {
        QModelIndex indexW = ui->tableWidget->model()->index(coordList[i].y, coordList[i].x);
        ui->tableWidget->selectionModel()->select(indexW, QItemSelectionModel::Select);
    } // for
}

void MainWindow::on_actionNew_window_triggered() {
    camView * ww = new camView( "http://192.168.1.2", "8080", NULL ) ;
    ww->show();
}

void MainWindow::on_actionWebView_triggered()
{
    webV * test = new webV( QUrl( "http://192.168.1.4:8080/?action=stream" ), "test" ) ;
    test->show();
}

void MainWindow::on_action_RecOption_triggered()
{

}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex it = ui->treeView->indexAt(pos);
    if ( it.row() == -1 ) return;
    QVariant strMac = it.model()->index( it.row(),  0).data();
    //qDebug() << strMac.toString();
    Global.selectedToRecord = Global.deviceMap.getByMac(strMac.toString());
    QMenu *popMenu =new QMenu(this);
    popMenu->addAction(ui->action_Watch);
    popMenu->addAction(ui->action_WatchAndRecord);
    popMenu->exec(QCursor::pos());

}

void MainWindow::on_action_Detect_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                           tr("Open location Info"), "",
                           tr("location Info (*.json);"));
        if (fileName.isEmpty()) return;

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
                    QMessageBox::information(this, tr("無法開啟檔案"),
                        file.errorString());
                    return ;
        } // if

        Global.deviceMap.initSaveParmeters( fileName.mid(fileName.lastIndexOf("/")+1));
        Global.areaData.read(&file);
        QStringList headers_Node;
        headers_Node << "Ip" << "Location" << "Coordnate" ;
        nodeView = new SortTreeView( ui->treeView_2, Global.areaData.toString(), headers_Node ) ;

        Global.areaData.getAllNodes(); //
        Global.areaData.update2View(ui->tableWidget); // update node info to tablewidget
        ui->action_Detect->setEnabled(false);
}

void MainWindow::on_action_WatchAndRecord_triggered()
{
    Global.selectedToRecord->startWatchAndRecord();
    //webV * test = new webV( QUrl( "http://192.168.1.4:8080/?action=stream" ) ) ;
    //test->show();

    //test->StartRecord("");
}

void MainWindow::on_action_Watch_triggered()
{
    Global.selectedToRecord->startWatch();
}

void MainWindow::on_treeView_2_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex it = ui->treeView_2->indexAt(pos);
    if ( it.row() == -1 ) return;
    QVariant vCoord = it.model()->index( it.row(),  2, it.parent()).data() ;

    if  ( vCoord.isValid() ) {

        QVariant vNodeIP = it.model()->index( it.row(),  0, it.parent()).data() ;
        Global.selectedNodeIPToRecord = vNodeIP.toString();
        QMenu *popMenu =new QMenu(this);
        popMenu->addAction(ui->action_NodeWatch);
        popMenu->addAction(ui->action_NodeWatchAndRecord);
        popMenu->exec(QCursor::pos());
    } // if


}

void MainWindow::on_action_NodeWatch_triggered()
{
    QDateTime local(QDateTime::currentDateTime());
    QString fileName = local.toString("yyyyMMdd") + "_" + local.toString("hhmmss") + "_" + Global.selectedNodeIPToRecord;
    webV * node = new webV( QUrl( "http://" + Global.selectedNodeIPToRecord + ":8080/?action=stream" ), fileName ) ;
    node->show();
}

void MainWindow::on_action_NodeWatchAndRecord_triggered()
{
    QDateTime local(QDateTime::currentDateTime());
    QString fileName = local.toString("yyyyMMdd") + "_" + local.toString("hhmmss") + Global.selectedNodeIPToRecord;
    webV * node = new webV( QUrl( "http://" + Global.selectedNodeIPToRecord + ":8080/?action=stream" ), fileName ) ;
    node->show();
    QString fileNameFormat = "./Record/Video/" + fileName + ".mp4";
    node->StartRecord(fileNameFormat.toLatin1().data());
}

void MainWindow::on_actionTestt_triggered()
{
\

    //MessageBoxA(NULL, "已開啟監控", "!!!!!", MB_OK);
    /*QProcess* dd = new QProcess();
    QStringList args ;
    args << "root" << "192.168.1.2" << "000000";
    qDebug() << args ;

    dd->start( "RemoteGuardian", args );*/
}
