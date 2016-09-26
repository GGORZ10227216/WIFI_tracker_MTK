#include "header/devicedata.h"

DeviceData::DeviceData()
{
  qDebug() << "test" ;
  //gDeviceMap = *new QMap<QString, DeviceData>() ;
}

DeviceData::DeviceData( QString input )
{
    QStringList dataList = input.split(QString(",")); //
    m_Mac = dataList[0];
    m_Db = dataList[1].toInt();
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



