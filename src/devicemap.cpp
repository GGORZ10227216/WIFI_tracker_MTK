#include "header/devicemap.h"
#include <QDebug>
DeviceMap::DeviceMap()
{

}

DeviceMap::~DeviceMap()
{
    //qDeleteAll( m_Map.begin(), m_Map.end() );  //  deletes all the values stored in "map"
    m_Map.clear();        //  removes all items from the map
}


void DeviceMap::updateData( DeviceData dData )
{

    if ( m_Map.isEmpty() && !m_Map.contains( dData.getMac()) ) // if m_Map isn't empty && if it is a new data
    {
        m_Map.insert(dData.getMac(), dData);
        qDebug() << "insert " << dData.m_Mac << " db " << dData.m_Db << endl;
        return;
    } // if

    QMap<QString, DeviceData>::iterator it = m_Map.find(dData.getMac()); // find position by key
    it.value().m_Db = dData.m_Db;
    qDebug() << "update " << it.value().m_Mac << " db to " << it.value().m_Db << endl;
}
