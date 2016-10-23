#include "header/devicedata.h"
#include "header/globalvariable.h"
extern GlobalV Global;
DeviceData::DeviceData()
{
    m_NeedUpdate = true;
    qDebug() << "test" ;
    //gDeviceMap = *new QMap<QString, DeviceData>() ;
}

DeviceData::DeviceData(QString in_Ip, QString input )
{
    QStringList dataList = input.split(QString(",")); //
    m_nodeIP = in_Ip;
    m_Mac = dataList[0];
    m_Db = dataList[1].toInt();
    m_Frame = dataList[2].toInt();
    m_NeedUpdate = true;
    m_DisplayState = Global.selectedNodeState;
    m_Camera = NULL;
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
    listRet << m_Mac << QString::number(m_Db) << QString::number(m_Frame);
    return listRet;
}

void DeviceData::startWatch()
{
    //if ( this->m_Camera->isRec ) return;
    QDateTime local(QDateTime::currentDateTime());
    QString fileName = local.toString("yyyyMMdd") + "_" + local.toString("hhmmss");
    this->m_Camera = new webV( QUrl( "http://" + m_nodeIP + ":8080/?action=stream" ), fileName.toLatin1().data() ) ;
    this->m_Camera->show();
}

void DeviceData::startWatchAndRecord()
{
    if ( this->m_Camera != NULL && this->m_Camera->isRecording() ) return;
    QDateTime local(QDateTime::currentDateTime());
    QString fileName = local.toString("yyyyMMdd") + "_" + local.toString("hhmmss");
    this->m_Camera = new webV( QUrl( "http://" + m_nodeIP + ":8080/?action=stream" ), fileName.toLatin1().data() ) ;
    this->m_Camera->show();

    qDebug() << fileName.toLatin1().data();
    QString fileNameFormat = fileName + ".mp4";
    this->m_Camera->StartRecord(fileNameFormat.toLatin1().data());
}

void DeviceData::changeCamera()
{
    if ( this->m_Camera == NULL || !this->m_Camera->isRecording() ) return;
    this->m_Camera->ChangeSrc(QUrl( "http://" + m_nodeIP + ":8080/?action=stream" ));
}

void DeviceData::stopRecord()
{
    if ( this->m_Camera == NULL || !this->m_Camera->isRecording() ) return;
    this->m_Camera->StopRecord();
}
