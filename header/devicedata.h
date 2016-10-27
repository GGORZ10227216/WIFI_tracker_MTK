#ifndef DEVICEDATA_H
#define DEVICEDATA_H
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QString>
#include <QMap>
#include <webv.h>
#include <QTimer>

class TmpDevice
{
public:
    QString ip = "";
    int coda = 0;
    int db = -101;
};

class DeviceData
{

public:
    int m_TimesLeave;
    bool m_NeedUpdate;
    QString m_nodeIP; // 蝭暺P
    QString m_Mac;
    qint64 m_Db;
    qint64 m_Frame;
    QString m_Location;
    TmpDevice tmpDevice;
    int m_DisplayState;
    int m_UpdateState;
    QMap<QString, TmpDevice> tmpMap;
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
    bool isCameraOpen()
    {
        if ( m_Camera == NULL ) return false;
        return m_Camera->isWatching ? true : false;
    }

    void checkDeviceExsit();

private:
    webV * m_Camera = NULL;
    QTimer *timer = NULL;

};

#endif // DEVICEDATA_H





