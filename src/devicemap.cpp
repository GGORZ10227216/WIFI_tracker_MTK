#include "header/devicemap.h"
#include <thread>
DeviceMap::DeviceMap()
{
    this->m_Ready = true;
    isChanged = true;
}

DeviceMap::~DeviceMap() {
    m_Map.clear();
}

bool DeviceMap::updateData( DeviceData dData ) {
    this->m_Ready = false;
    if ( m_Map.isEmpty() ) {
        m_Map.insert(dData.getMac(), dData);
    } // if
    else {
        if ( !m_Map.contains( dData.getMac()) ) {
            m_Map.insert(dData.getMac(), dData);
        } // if
        else {
            QMap<QString, DeviceData>::iterator it = m_Map.find(dData.getMac());
            if ( it.value().m_nodeIP.compare( dData.m_nodeIP ) != 0 ) {
                if ( it.value().m_Db < dData.m_Db ) {
                    it.value().m_nodeIP = dData.m_nodeIP;
                    it.value().m_Db = dData.m_Db;
                    it.value().m_Frame = dData.m_Frame;
                    it.value().m_NeedUpdate = true;
                } // if
                else return false;
            } // if
            else {
                 it.value().m_Db = dData.m_Db;
                 it.value().m_Frame = dData.m_Frame;
                 it.value().m_NeedUpdate = true ;
            } // else
        } // elseA
    } // else

    this->m_Ready = true ;
    return true;
}

bool DeviceMap::DeleteData( QString strKey ) {
   return m_Map.remove(strKey);
}

DeviceData *DeviceMap::At( qint64 index ) {
    if ( index >= m_Map.size() || index < 0 )
        return NULL;

    return &*(m_Map.begin() + index);
}

DeviceData* DeviceMap::getLast() {
    return &*(m_Map.end()-1);
}

qint64 DeviceMap::size() {
    return m_Map.size();
}

bool DeviceMap::setDisplayState( QString strKey, int b) {
    for ( QMap<QString, DeviceData>::iterator it = m_Map.begin(); it != m_Map.end(); it++ ) {
        if ( it.value().m_nodeIP.compare(strKey) == 0 ) {
            it.value().m_DisplayState = b;
            it.value().m_NeedUpdate = true;
        } // if
    } // for

    return true;
}
