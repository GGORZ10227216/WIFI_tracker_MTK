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
    qDebug() << "AreaData read";
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

    for ( int i = 1; i < json.size(); i++ ) // 0 is mapdata
    {
        Machine mM((json.begin()+i).key());
        mM.read(json[(json.begin()+i).key()].toObject());
        this->m_MachineList.push_back(mM);
    } // for


    // qDebug() << "readAreaInfo= " << loadDoc.array()[0];

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
