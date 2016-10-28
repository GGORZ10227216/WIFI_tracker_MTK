#ifndef DEVICEMAP_H
#define DEVICEMAP_H
#include "header/devicedata.h"
#include <QDebug>
#include <QString>
#include <atomic>
#include <QFile>
class DeviceMap
{
public:
    std::atomic_bool m_Ready;

    DeviceMap();
    DeviceMap(const DeviceMap & origin);
    ~DeviceMap();
    bool updateData(DeviceData & dData );
    DeviceData* At( qint64 index );
    DeviceData *getLast();
    DeviceData* getByMac( QString in_mac)
    {
        return &*m_Map.find(in_mac);
    }

    bool DeleteData(QString strKey );
    qint64 size(); 
    bool setDisplayState(QString strKey, int b);
    void saveToFile(DeviceData dData , bool isIn);
    void saveToCSV( DeviceData dData , bool isIn );
    void saveToJSON( DeviceData dData , bool isIn );
    void initSaveParmeters( QString in_location );
    bool CheckChange( DeviceData & oldOne, DeviceData & newOne ) ;

    void clear()
    {
        m_Map.clear();
    }

    QString getNodeIpByMac( QString mac )
    {
        return m_Map.find(mac).value().m_nodeIP;
    }

private:
    QMap<QString, DeviceData> m_Map;
    bool isChanged;
    QString m_strLocation;
    QFile* fileCSV = NULL;
    QFile* fileJSON = NULL;
    QTextStream outCSV;
    QTextStream outJSON;
    QVariantList dataListForJson;

};

#endif // DEVICEMAP_H


