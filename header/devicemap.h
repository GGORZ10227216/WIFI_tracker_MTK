#ifndef DEVICEMAP_H
#define DEVICEMAP_H
#include "header/devicedata.h"
#include <QDebug>
#include <QString>
class DeviceMap
{
public:
    DeviceMap();
    ~DeviceMap();
    void updateData( DeviceData dData );
    DeviceData* At( qint64 index );
    DeviceData *getLast();
    bool DeleteData(QString strKey );
    qint64 size();
private:
    QMap<QString, DeviceData> m_Map;
};

#endif // DEVICEMAP_H


