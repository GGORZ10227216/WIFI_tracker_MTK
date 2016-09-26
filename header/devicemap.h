#ifndef DEVICEMAP_H
#define DEVICEMAP_H
#include "header/devicedata.h"
class DeviceMap
{
public:
    DeviceMap();
    ~DeviceMap();
    void updateData( DeviceData dData );
private:
    QMap<QString, DeviceData> m_Map;
};

#endif // DEVICEMAP_H


