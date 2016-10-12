#ifndef NODEDATA_H
#define NODEDATA_H
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QString>
#include <QJsonObject>
struct Coordinate
{
    int x;
    int y;
};

struct NodeInfo
{
    Coordinate Coord;
    QString Ip;
    QString Mac;
};

class NodeData
{
public:
    NodeData();
    NodeData(QString in_Location );
    // DeviceData(QVariant mac);
    ~NodeData();
    bool read(const QJsonObject &json);
    QString getLocation(){ return m_Location; }
    //QList<NodeData> getNodeList(){ return m_InfoList; }
    QString toString();
    QList<NodeInfo> getInfoList(){ return m_InfoList; }
    void getNodeCoord( QString strIP, QList<Coordinate>& coordList );
private:
    QString m_Location;
    QList<NodeInfo> m_InfoList;
};
#endif // NODEDATA_H
