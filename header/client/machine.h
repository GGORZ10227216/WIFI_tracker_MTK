#ifndef MACHINE_H
#define MACHINE_H
#include "header/client/nodedata.h"

class Machine
{
public:
    Machine();
    Machine(QString in_Location);
    // DeviceData(QVariant mac);
    ~Machine();
    bool read(const QJsonObject &json);
    //QString toString();
    //QStringList toStringList();
    QString getLocation(){ return m_Location; }
    int getChannel(){ return m_Channel; }
    NodeInfo getNodeInfo(){ return m_Info; }
    QList<NodeData> getNodeList(){ return m_NodeList; }
    QString toString();
    void getNodeCoord( QString strIP, QList<Coordinate>& coordList );
    QString getNodeLocation( QString strIP );
private:
    QString m_Location;
    int m_Channel;
    NodeInfo m_Info;
    QList<NodeData> m_NodeList;
};
#endif // MACHINE_H
