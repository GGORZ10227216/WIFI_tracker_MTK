#ifndef DEVICEMAP_H
#define DEVICEMAP_H
#include "header/devicedata.h"
#include <QDebug>
#include <QString>
#include <atomic>

class DeviceMap
{
public:
    std::atomic_bool m_Ready;
    DeviceMap();
    ~DeviceMap();
    bool updateData( DeviceData dData );
    DeviceData* At( qint64 index );
    DeviceData *getLast();
    bool DeleteData(QString strKey );
    qint64 size(); 
    bool setDisplayState(QString strKey, int b);
    QString getNodeIpByMac( QString mac )
    {
        return m_Map.find(mac).value().m_nodeIP;
    }

private:
    QMap<QString, DeviceData> m_Map;
    bool isChanged;

};

#endif // DEVICEMAP_H


