#include "header/client/areadata.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
AreaData::AreaData()
{

}

AreaData::~AreaData()
{

}

bool AreaData::read(const QString fileName)
{
    //qDebug() << "AreaData read";
    QFile loadFile(fileName);
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    } // if

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();
    this->m_Location = json["AreaName"].toString();
    json = json["TracerInfo"].toObject();
    QJsonObject json_Size = json["MapData"].toObject();
    QJsonArray mapArr = json_Size["Size"].toArray();

    this->m_MapSize.bass = mapArr[0].toInt();
    this->m_MapSize.machine = mapArr[1].toInt();

    qDebug() << mapArr[1].toInt() ;

    for ( int i = 0; i < json.size(); i++ ) // 0 is mapdata
    {
        if ( (json.begin()+i).key() != "MapData" ) {
            Machine mM((json.begin()+i).key());
            mM.read(json[(json.begin()+i).key()].toObject());
            this->m_MachineList.push_back(mM);
        } // if
    } // for




    loadFile.close();
    return true;
}

QString AreaData::toString()
{
    QString strRet;
    for ( int i = 0; i < this->m_MachineList.size(); i++ )
    {
      strRet += m_MachineList[i].toString();
    } // for

    return m_Location + '\n' + strRet;
}

void AreaData::update2View( QTableWidget* tView )
{
    static Coordinate sizeV;
    sizeV.x = sizeV.y = 0;

    for ( int i = 0; i < m_NodeList.size(); i++ )
    {

        QList<NodeInfo> nList = m_NodeList[i].getInfoList();
        for ( int j = 0; j < nList.size(); j++ )
        {
            sizeV.x = nList[j].Coord.x > sizeV.x ? nList[j].Coord.x : sizeV.x;
            sizeV.y = nList[j].Coord.y > sizeV.y ? nList[j].Coord.y : sizeV.y;

            tView->setRowCount(sizeV.y+1);
            tView->setColumnCount(sizeV.x+1);
            tView->setItem(nList[j].Coord.y, nList[j].Coord.x, new QTableWidgetItem(m_NodeList[i].getLocation()));
        } // for
    } // for

    /*qDebug() << tView->model()->rowCount() << tView->model()->columnCount();
    for ( int i = 0; i < tView->model()->rowCount(); i++ )
        for ( int j = 0; j < tView->model()->columnCount(); j++)
        {
            tView->model()->setHeaderData(i, Qt::Vertical, "444");
            tView->model()->setHeaderData(j, Qt::Horizontal, "555");

        } // for

    emit tView->model()->headerDataChanged(Qt::Horizontal, 0 , tView->model()->columnCount());
    emit tView->model()->headerDataChanged(Qt::Vertical, 0 , tView->model()->rowCount());*/
}

void AreaData::getAllNodes()
{
    m_NodeList.clear();
    for ( int i = 0; i < m_MachineList.size(); i++  )
        m_NodeList << m_MachineList[i].getNodeList();
}

void AreaData::getNodeCoord( QString strIP, QList<Coordinate>& coordList )
{
    for ( int i = 0; i < m_MachineList.size(); i++  )
        m_MachineList[i].getNodeCoord(strIP, coordList);
}
