#include "header/client/nodedata.h"
#include "header/globalvariable.h"
#include <QJsonObject>
#include <QJsonArray>
extern GlobalV Global;

NodeData::NodeData()
{

}

NodeData::NodeData(QString in_Location , QString in_Mac, int in_Channel)
{
    this->m_Location = in_Location;
    this->m_Mac = in_Mac;
    this->m_Channel = in_Channel;
}


NodeData::~NodeData()
{

}

bool NodeData::read(  const QJsonObject &json)
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
        if ( i % 2 == 0 )
        {
            qDebug() << str << "----------------";
            //if ( str.compare("192.168.1.4") != 0 )// "10:C3:7B:41:10:58", 11
                Global.n_mana.connectSever(str, 48763, this->m_Mac, this->m_Channel  );//"F0:79:59:D1:71:D4", 6
                //qDebug() << str << this->m_Mac << this->m_Channel;
                Global.nodeMacMap[this->m_Mac] = this->m_Location;
                Global.nodeIp2AreaMap[str] = this->m_Location;

        } // if

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
        Global.nodeMacMap[nI.Mac] = nI.Ip;
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

void NodeData::getNodeCoord( QString strIP, QList<Coordinate>& coordList )
{
    for ( int i = 0; i < m_InfoList.size(); i++  )
        if ( strIP.compare( m_InfoList[i].Ip ) == 0 )
            coordList << m_InfoList[i].Coord;
}

QString NodeData::getNodeLocation( QString strIP )
{
    for ( int i = 0; i < m_InfoList.size(); i++  )
        if ( strIP.compare( m_InfoList[i].Ip ) == 0 )
            return this->m_Location;
    return "";
}
