#ifndef DEVICEDATA_H
#define DEVICEDATA_H
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QString>
#include <QMap>

class DeviceData
{
public:
    QString m_Mac;
    qint64 m_Db;
    QString getMac();
    DeviceData();
    DeviceData(QString input);
    // DeviceData(QVariant mac);
    ~DeviceData();

private:

};

#endif // DEVICEDATA_H





