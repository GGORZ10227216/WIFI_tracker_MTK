#ifndef DEVICEDATA_H
#define DEVICEDATA_H
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QString>
#include <QMap>
#include <webv.h>
class DeviceData
{
public:
    bool m_NeedUpdate;
    QString m_nodeIP; // 蝭暺P
    QString m_Mac;
    qint64 m_Db;
    qint64 m_Frame;
    QString m_Location;
    int m_DisplayState;
    int m_UpdateState;
    void startWatch();
    void startWatchAndRecord();
    void changeCamera();
    void stopRecord();
    QString getMac();
    DeviceData();
    DeviceData(QString in_Ip, QString input);
    // DeviceData(QVariant mac);
    ~DeviceData();
    QString toString();
    QStringList toStringList();
    static int getColumnCount(){return 2;} // 3?olumn
private:
    webV * m_Camera;
};

#endif // DEVICEDATA_H





