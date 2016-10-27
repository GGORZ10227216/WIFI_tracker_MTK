#include "header/devicedata.h"
#include "header/globalvariable.h"
#include <QMessageBox>
extern GlobalV Global;

DeviceData::DeviceData()
{
    m_NeedUpdate = true;
    qDebug() << "test" ;
    //gDeviceMap = *new QMap<QString, DeviceData>() ;
}

void DeviceData::checkDeviceExsit()
{
    if ( this->m_Db == -100 )
        m_TimesLeave++;
}

DeviceData::DeviceData(QString in_Ip, QString input )
{
    QStringList dataList = input.split(QString(",")); //
    m_nodeIP = in_Ip;
    m_Mac = dataList[0];
    m_Db = dataList[1].toInt();
    m_Frame = 0;//dataList[2].toInt();
    m_NeedUpdate = true;
    m_DisplayState = Global.selectedNodeState;
    m_UpdateState = Global.updateNewestNumber;
    m_Camera = NULL;
    m_Location = Global.areaData.getNodeLocation(m_nodeIP);
    m_TimesLeave = 0;
    //qDebug() << "----------------------------" << m_Location;
}
/*
DeviceData::DeviceData( QVariant in_mac/*, QVariant in_db)
{
   // mac = in_mac;
    //db = in_db;
}
*/
DeviceData::~DeviceData()
{

}

bool DeviceData::isCameraOpen()
{
    if ( m_Camera == NULL ) return false;
    return m_Camera->isWatching ? true : false;
}

QString DeviceData::getMac()
{
    return m_Mac;
}

QString DeviceData::toString() // format aa,bb,cc,dd...
{
    QString strRet = m_Mac + ",";
    strRet += QString::number(m_Db);
    strRet += ",";
    strRet += QString::number(m_Frame);
    return strRet;
}

QStringList DeviceData::toStringList()
{
    QStringList listRet;
    listRet << m_Mac << this->m_Location << QString::number(m_Db);
    return listRet;
}

void DeviceData::startWatch()
{
    if ( this->m_Camera != NULL && (this->m_Camera->isWatching || this->m_Camera->isRecording()) ) {
        QMessageBox::information(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("此裝置監控以開啟"));
        return;
    } // if

    qDebug() << "fffffffffffffffffffffffffffff" << m_nodeIP;
    //
    QDateTime local(QDateTime::currentDateTime());
    QString fileName = local.toString("yyyyMMdd") + "_" + local.toString("hhmmss");

    this->m_Camera = new webV( QUrl( "http://" + m_nodeIP + ":8080/?action=stream" ), this, fileName.toLatin1().data() ) ;
    this->m_Camera->show();
    this->m_Camera->isWatching = true;
}

void DeviceData::startWatchAndRecord()
{
    if ( this->m_Camera != NULL && (this->m_Camera->isRecording() || this->m_Camera->isWatching) ) {
        QMessageBox::information(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("此裝置監控以開啟"));
        return;
    } // if

    QDateTime local(QDateTime::currentDateTime());
    QString fileName = local.toString("yyyyMMdd") + "_" + local.toString("hhmmss");
    this->m_Camera = new webV( QUrl( "http://" + m_nodeIP + ":8080/?action=stream" ), this, fileName.toLatin1().data() ) ;
    this->m_Camera->show();
    this->m_Camera->isWatching = true;
    qDebug() << fileName.toLatin1().data();
    QString fileNameFormat = "./Record/Video/" + fileName + ".mp4";
    this->m_Camera->StartRecord(fileNameFormat.toLatin1().data());
}

void DeviceData::changeCamera()
{
    //qDebug() << "CHECK------------------------------------------------------------" << m_nodeIP;
    if ( this->m_Camera == NULL ) return;
    //qDebug() << "IN------------------------------------------------------------" << m_nodeIP;
    this->m_Camera->ChangeSrc(QUrl( "http://" + m_nodeIP + ":8080/?action=stream" ));
}

void DeviceData::stopRecord()
{
    if ( this->m_Camera == NULL || !this->m_Camera->isRecording() ) return;
    this->m_Camera->StopRecord();
}
