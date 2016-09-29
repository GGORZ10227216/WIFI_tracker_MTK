#include "header/client/nodedata.h"
#include <QJsonObject>
#include <QJsonArray>
NodeData::NodeData()
{

}

NodeData::NodeData(QString in_Location )
{
    this->m_Location = in_Location;
}


NodeData::~NodeData()
{

}

bool NodeData::read(const QJsonObject &json)
{
    //qDebug() << "NodeData read";
    QJsonArray arr = json["Cord"].toArray();
    QList<Coordinate> coordList;
    QList<QString> infoList;
    for ( int i = 0; i < arr.size(); i += 2 ) // format (x,y) (x1,y1)
    {
        Coordinate cd;
        cd.x =arr[i].toInt();
        cd.y = arr[i+1].toInt();
        coordList.push_back(cd);
    } // for

    arr = json["Info"].toArray();
    for ( int i = 0; i < arr.size(); i ++ ) // format (ip,mac) (ip1,mac1)
    {
        QString str = arr[i].toString();
        infoList.push_back(str);
    } // for

    int nOfCoord = coordList.size();
    int nOfInfo = infoList.size() / 2;
    // 2 coord vs 1 ip || 2 coord vs 2 ip
    for ( int l = 0, lI = 0; l < nOfCoord; l++ )
    {
        NodeInfo nI;
        nI.Coord = coordList[l];
        nI.Ip = infoList[lI];
        nI.Mac = infoList[lI+1];
        if ( nOfCoord == nOfInfo )
            lI += 2;
        this->m_InfoList.push_back(nI);
    } // for

    return true;
}

QString NodeData::toString(){
    QString strRet = "";
    for ( int i = 0; i < m_InfoList.size(); i++ )
    {
        strRet += ' ';
        strRet += ' ' + m_InfoList[i].Ip + "," + m_Location + ',' + ( '(' + QString::number(m_InfoList[i].Coord.x) + '-' + QString::number(m_InfoList[i].Coord.y) + ')' ) + '\n';
    } // for

    return strRet;
}
