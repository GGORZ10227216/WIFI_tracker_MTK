#ifndef DEVICEMAP_H
#define DEVICEMAP_H
#include "header/devicedata.h"
#include <QDebug>
#include <QString>
class DeviceMap
{
public:
    std::atomic<bool> m_Ready;
    DeviceMap();
    ~DeviceMap();
    void updateData( DeviceData dData );
    DeviceData* At( qint64 index );
    DeviceData *getLast();
    bool DeleteData(QString strKey );
    qint64 size(); 
    bool setDisplayState(QString strKey, int b);
private:
    QMap<QString, DeviceData> m_Map;
    bool isChanged;

};

#endif // DEVICEMAP_H


