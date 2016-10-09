#include "header/devicedata.h"
#include "header/globalvariable.h"
extern GlobalV Global;
DeviceData::DeviceData()
{
    m_NeedUpdate = true;
    qDebug() << "test" ;
    //gDeviceMap = *new QMap<QString, DeviceData>() ;
}

DeviceData::DeviceData( QString input )
{
    QStringList dataList = input.split(QString(",")); //
    m_Mac = dataList[0];
    m_Db = dataList[1].toInt();
    m_Frame = dataList[2].toInt();
    m_NeedUpdate = true;
    m_DisplayState = Global.selectedNodeState;
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

