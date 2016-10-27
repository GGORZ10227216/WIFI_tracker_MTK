#include "header/client/machine.h"
#include "header/client/nodedata.h"
#include <QJsonObject>
#include <QDebug>
#include "header/globalvariable.h"
extern GlobalV Global;
Machine::Machine()
{

}

Machine::Machine(QString in_Location )
{
    this->m_Location = in_Location;
}

Machine::~Machine()
{

}

bool Machine::read(const QJsonObject &json)
{
    //qDebug() << "Machine read";
    this->m_Channel = json["WorkingChannel"].toInt();
    this->m_Info.Ip = json["IP"].toString();
    this->m_Info.Mac = json["Bssid"].toString();
    QJsonObject jsonM = json["NodeList"].toObject();
    for ( int i = 0; i < jsonM.size(); i++ )
    {
        NodeData nD((jsonM.begin()+i).key(), m_Info.Mac, m_Channel);
        nD.read( jsonM[(jsonM.begin()+i).key()].toObject());
        this->m_NodeList.push_back(nD);    
    } // for


    /*
      QJsonObject obj1 = json["TracerInfo"].toObject();
      qDebug() << obj1.begin().key();
      QJsonObject obj2 = obj1[obj1.begin().key()].toObject();
      qDebug() << "JSON=> " << obj2["Bssid"].toString();
      */
    return true;
}

QString Machine::toString(){
    QString strRet = "";
    for ( int i = 0; i < m_NodeList.size(); i++ )
    {
        strRet +=  m_NodeList[i].toString();
    } // for

    return ' ' + m_Info.Ip + "," + m_Location + ',' + '\n' + strRet;
}

void Machine::getNodeCoord( QString strIP, QList<Coordinate>& coordList )
{
    for ( int i = 0; i < m_NodeList.size(); i++  )
       m_NodeList[i].getNodeCoord(strIP, coordList);
}

QString Machine::getNodeLocation( QString strIP )
{
    QString ss;
    for ( int i = 0; i < m_NodeList.size(); i++  )
       if ( (ss = m_NodeList[i].getNodeLocation(strIP)).size() > 0 )
            return ss;
    return "";
}
