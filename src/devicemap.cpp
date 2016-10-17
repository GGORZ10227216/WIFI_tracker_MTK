#include "header/devicemap.h"
#include <thread>
DeviceMap::DeviceMap()
{
    this->m_Ready = true;
    isChanged = true;
}

DeviceMap::~DeviceMap()
{
    //qDeleteAll( m_Map.begin(), m_Map.end() );  //  deletes all the values stored in "map"
    m_Map.clear();        //  removes all items from the map
}


bool DeviceMap::updateData( DeviceData dData )
{
    //while ( !this->m_Ready.load() )
    //    std::this_thread::yield(); // 霈cpu霈隞犖??
    //static int up = 0;/
    //qDebug() << up++ << "-----------update view--------------";
    this->m_Ready = false; // ???瑁?
    if ( m_Map.isEmpty() ) // if m_Map isn't empty
    {
        m_Map.insert(dData.getMac(), dData);
        //qDebug() << "insert2 " << dData.m_Mac << " db " << dData.m_Db << endl;
    } // if
    else // if m_Map is empty
    {
        //qDebug() << "is not empty" << endl;
        if ( !m_Map.contains( dData.getMac()) ) // if it is a new data
        {
            m_Map.insert(dData.getMac(), dData);
            //qDebug() << "insert1 " << dData.m_Mac << " db " << dData.m_Db << endl;
        } // if
        else // if data is exsit
        {
            QMap<QString, DeviceData>::iterator it = m_Map.find(dData.getMac()); // find position by key
            if ( it.value().m_nodeIP.compare( dData.m_nodeIP ) != 0 ) // 銝?蝭暺?b?亥?0??
            {
                if ( it.value().m_Db < dData.m_Db )
                {
                    it.value().m_nodeIP = dData.m_nodeIP;
                    it.value().m_Db = dData.m_Db;
                    it.value().m_Frame = dData.m_Frame;
                    it.value().m_NeedUpdate = true; // need to update
                } // if
                else return false;
            } // if
            else // ??暺?交??
            {
                 it.value().m_Db = dData.m_Db;
                 it.value().m_Frame = dData.m_Frame;
                 it.value().m_NeedUpdate = true; // need to update
            } // else


            //qDebug() << "update " << it.value().m_Mac << " db to " << it.value().m_Db << endl;
        } // elseA
    } // else

    this->m_Ready = true; // ?瑁?蝯?
    return true;
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

bool DeviceMap::setDisplayState( QString strKey, int b)
{
    //while ( !this->m_Ready.load() )
    //    std::this_thread::yield(); // 霈cpu霈隞犖??
    //this->m_Ready = false; // ???瑁?
    for ( QMap<QString, DeviceData>::iterator it = m_Map.begin(); it != m_Map.end(); it++ )
    {
        if ( it.value().m_nodeIP.compare(strKey) == 0 )
        {
            // qDebug() << strKey << ", " << it.value().m_DisplayState;
            it.value().m_DisplayState = b;
            it.value().m_NeedUpdate = true;
            //this->m_Ready = true; // ?瑁?蝯?
            //return true;
        } // if
    } // for

    //this->m_Ready = true; // ?瑁?蝯?
    return true;
}
