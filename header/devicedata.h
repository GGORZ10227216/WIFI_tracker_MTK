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
    bool m_NeedUpdate;
    QString m_nodeIP; // 蝭暺P
    QString m_Mac;
    qint64 m_Db;
    qint64 m_Frame;
    int m_DisplayState;
    QString getMac();
    DeviceData();
    DeviceData(QString in_Ip, QString input);
    // DeviceData(QVariant mac);
    ~DeviceData();
    QString toString();
    QStringList toStringList();
    static int getColumnCount(){return 3;} // 3?olumn
private:
};

#endif // DEVICEDATA_H





