#include "header/devicemap.h"

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

    if ( m_Map.isEmpty() ) // if m_Map isn't empty
    {
        m_Map.insert(dData.getMac(), dData);
        qDebug() << "insert2 " << dData.m_Mac << " db " << dData.m_Db << endl;
    } // if
    else // if m_Map is empty
    {
        //qDebug() << "is not empty" << endl;
        if ( !m_Map.contains( dData.getMac()) ) // if it is a new data
        {
            m_Map.insert(dData.getMac(), dData);
            qDebug() << "insert1 " << dData.m_Mac << " db " << dData.m_Db << endl;
        } // if
        else // if data is exsit
        {
            QMap<QString, DeviceData>::iterator it = m_Map.find(dData.getMac()); // find position by key
            it.value().m_Db = dData.m_Db;
            it.value().m_NeedUpdate = true; // need to update
            qDebug() << "update " << it.value().m_Mac << " db to " << it.value().m_Db << endl;
        } // else
    } // else

}

bool DeviceMap::DeleteData( QString strKey )
{
   return m_Map.remove(strKey);
}

DeviceData *DeviceMap::At( qint64 index )
{
    if ( index >= m_Map.size() || index < 0 )
        return NULL;

    return &*(m_Map.begin() + index);
}

DeviceData* DeviceMap::getLast()
{
    return &*(m_Map.end()-1);
}

qint64 DeviceMap::size()
{
    return m_Map.size();
}
