﻿#include "header/devicemap.h"
#include <thread>
#include <QDateTime>
#include <QVariantList>
#include <QJsonDocument>
#include <header/globalvariable.h>
extern GlobalV Global;
DeviceMap::DeviceMap()
{
    this->m_Ready = true;
    isChanged = true;
}

DeviceMap::~DeviceMap()
{
    //qDeleteAll( m_Map.begin(), m_Map.end() );  //  deletes all the values stored in "map"
    m_Map.clear();        //  removes all items from the map
    if ( fileCSV != NULL && fileJSON != NULL )
    {
        QJsonDocument jsonDocument = QJsonDocument::fromVariant(dataListForJson);
        if (!jsonDocument.isNull())
        {
            outJSON << jsonDocument.toJson();
            //qDebug() << jsonDocument.toJson();
        }
        else qDebug() << "save json error!!";

        fileCSV->close();
        fileJSON->close();
    } // if
}

void DeviceMap::initSaveParmeters( QString in_location )
{
    m_strLocation = in_location;
    QDateTime local(QDateTime::currentDateTime());
    // initial csv
    fileCSV = new QFile( "./Record/Data/" + local.toString("yyyyMMdd") + "_"  + this->m_strLocation + ".csv");
    fileCSV->open( QIODevice::WriteOnly | QIODevice::Text);
    outCSV.setDevice(fileCSV);
    // initial json
    fileJSON = new QFile( "./Record/Data/" + local.toString("yyyyMMdd") + "_"  + this->m_strLocation + ".json");
    fileJSON->open(QIODevice::WriteOnly | QIODevice::Text);
    outJSON.setDevice(fileJSON);

}

void DeviceMap::saveToFile(DeviceData dData , bool isIn)
{
    saveToCSV(dData, isIn);
    saveToJSON( dData , isIn);
}

void DeviceMap::saveToCSV( DeviceData dData, bool isIn )
{
    QList<Coordinate> coordList;
    Global.areaData.getNodeCoord(dData.m_nodeIP, coordList);
    QString coords = "";
    for( int i = 0; i < coordList.size(); i++ )
    {
        coords += ( "(" + QString::number(coordList[i].y) + "-" + QString::number(coordList[i].x) + ")" );
    } // for

    QDateTime local(QDateTime::currentDateTime());
    QString strIsIn = isIn ? "In" : "Out";
    outCSV << dData.m_Mac << "," << local.toString("hh:mm:ss") << "," << coords << "," << strIsIn << "\n";
}

void DeviceMap::saveToJSON( DeviceData dData, bool isIn )
{
    QList<Coordinate> coordList;
    Global.areaData.getNodeCoord(dData.m_nodeIP, coordList);
    QString coords = "";
    for( int i = 0; i < coordList.size(); i++ )
    {
        coords += ( "(" + QString::number(coordList[i].y) + "-" + QString::number(coordList[i].x) + ")" );
    } // for

    QString strIsIn = isIn ? "In" : "Out";


    QDateTime local(QDateTime::currentDateTime());
    QVariantMap vMap;
    vMap.insert("Mac", dData.m_Mac);
    vMap.insert("Time", local.toString("hh:mm:ss"));
    vMap.insert("Coordinate", coords);
    vMap.insert("Status", strIsIn);
    //qDebug() << "----------->" << vMap["Mac"];
    dataListForJson << vMap;
}

bool DeviceMap::CheckChange( DeviceData & oldOne, DeviceData & newOne ) {
    if ( oldOne.m_Db < newOne.m_Db &&
         ( newOne.m_Db != -100 || ( ( -5 < newOne.m_Db && newOne.m_Db <= 0) )) ) {

        if ( newOne.m_Mac == "18:CF:5E:75:18:62" ) {
            qDebug() << "-------------------------------" ;
            qDebug() << "From: " << oldOne.m_nodeIP
                     << "(" << oldOne.m_Db << ")" ;
            qDebug() << "To: " << newOne.m_nodeIP
                     << "(" << newOne.m_Db << ")" ;
            //qDebug() << "Last request: " << oldOne.tmpDevice.ip
            //         << "(" << oldOne.tmpDevice.db << ")" ;
            //qDebug() << "OLD_CODA: " << oldOne.tmpDevice.coda ;
        } // if

        // it oldOne tmp

        if ( !oldOne.tmpMap.contains(newOne.m_nodeIP) )// if request node not in tmp map than insert the node info
        {
            TmpDevice tmp; // coda = 0
            oldOne.tmpMap[newOne.m_nodeIP] = tmp;
        } // if
        else // already in tmp map
        {
            //QMap<QString, TmpDevice>::iterator it = oldOne.tmpMap.find(newOne.m_nodeIP);
            if ( oldOne.m_Db < newOne.m_Db ) { // if node ip in tmpmap and request db > oldone db
                oldOne.tmpMap[newOne.m_nodeIP].coda++;
                if ( oldOne.tmpMap[newOne.m_nodeIP].coda > 1 )
                {
                    //for ( QMap<QString, TmpDevice>::iterator ii = oldOne.tmpMap.begin(); ii < oldOne.tmpMap.end(); ii++ )
                    //    ii->coda = 0;
                    oldOne.tmpMap.clear(); // clear map
                    return true;
                }
            } // if
            else
                oldOne.tmpMap[newOne.m_nodeIP].coda = 0;
        } // else
        /*QMap<QString, TmpDevice>::iterator it = oldOne.tmpMap.find(newOne.m_nodeIP);
        if ( it != oldOne.tmpMap.end() && oldOne.m_Db < newOne.m_Db ) { // if node ip in tmpmap and request db > oldone db
            oldOne.tmpMap[newOne.m_nodeIP].coda++;
            if ( oldOne.tmpMap[newOne.m_nodeIP].coda >= 5 )
            {
                //for ( QMap<QString, TmpDevice>::iterator ii = oldOne.tmpMap.begin(); ii < oldOne.tmpMap.end(); ii++ )
                //    ii->coda = 0;
                QMap<QString, TmpDevice>().swap(oldOne.tmpMap.swap); // clear map
                return true;
            }
        } // if
        else if ( it == oldOne.tmpMap.end() )// if request node not in tmp map than insert the node info
        {
            TmpDevice tmp; // coda = 0
            oldOne.tmpMap[newOne.m_nodeIP] = tmp;
        } // else if*/
    } // if
    else
        return false ;
    return false ;
} //CheckChange

bool DeviceMap::updateData( DeviceData & dData )
{
    //while ( !this->m_Ready.load() )
    //    std::this_thread::yield(); // 霈cpu霈隞犖??
    //static int up = 0;/


    this->m_Ready = false; // ???瑁?

    if ( m_Map.isEmpty() ) // if m_Map isn't empty
    {
        //if ( dData.m_Db >= -70 )
        //{
            m_Map.insert(dData.getMac(), dData);
            saveToFile( dData, true );
            //qDebug() << (m_Map.begin())->m_nodeIP << (m_Map.begin())->m_Mac;
       // } // if
        //qDebug() << "insert2 " << dData.m_Mac << " db " << dData.m_Db << endl;
    } // if
    else // if m_Map is empty
    {
        //qDebug() << "is not empty" << endl; qDebug() << dData.m_nodeIP << dData.m_Mac;
        if ( !m_Map.contains( dData.getMac()) ) // if it is a new data
        {

            //if ( dData.m_Db >= -70 )
            //{
                m_Map.insert(dData.getMac(), dData);
                //qDebug() << (m_Map.end()-1)->m_nodeIP << (m_Map.end()-1)->m_Mac;
                saveToFile( dData, true );

            //} // if
            //qDebug() << "insert1 " << dData.m_Mac << " db " << dData.m_Db << endl;
        } // if
        else // if data is exsit
        {
            QMap<QString, DeviceData>::iterator it = m_Map.find(dData.getMac()); // find position by key
            if ( it.value().m_nodeIP.compare( dData.m_nodeIP ) != 0 ) // 銝?蝭暺?b?亥?0??
            {
                if ( CheckChange( it.value(), dData ) )
                {

                    saveToFile( it.value(), false ); // leave
                    it.value().m_UpdateState = Global.updateNewestNumber;
                    it.value().m_nodeIP = dData.m_nodeIP;
                    it.value().m_Db = dData.m_Db;
                    it.value().m_Frame = dData.m_Frame;
                    it.value().m_NeedUpdate = true; // need to update
                    it.value().m_Location = dData.m_Location;
                    saveToFile( it.value(), true ); // in
                    it.value().changeCamera();

                    //qDebug() << it.value().m_nodeIP << it.value().m_Mac;
                } // if
                else return false;
            } // if
            else // ??暺?交??
            {
                 it.value().m_UpdateState = Global.updateNewestNumber;
                 it.value().m_Db = dData.m_Db;
                 it.value().m_Frame = dData.m_Frame;
                 it.value().m_NeedUpdate = true; // need to update
                 if ( dData.m_Db == -100 )
                     saveToFile( it.value(), false ); // leave
                     //qDebug() << it.value().m_nodeIP << it.value().m_Mac;

            } // else


            //qDebug() << "update " << it.value().m_Mac << " db to " << it.value().m_Db << endl;
        } // elseA
    } // else

    this->m_Ready = true; // ?瑁?蝯?
    return true;
}

bool DeviceMap::DeleteData( QString strKey )
{
   m_Map.find(strKey).value().stopRecord();
   return m_Map.remove(strKey);
}

DeviceData *DeviceMap::At( qint64 index )
{
    if ( index >= m_Map.size() || index < 0 )
        return NULL;

    return &*(m_Map.begin() + index);
}

DeviceData* DeviceMap::getLast()
{
    return &*(m_Map.end()-1);
}

qint64 DeviceMap::size()
{
    return m_Map.size();
}

bool DeviceMap::setDisplayState( QString strKey, int b)
{
    //while ( !this->m_Ready.load() )
    //    std::this_thread::yield(); // 霈cpu霈隞犖??
    //this->m_Ready = false; // ???瑁?
    for ( QMap<QString, DeviceData>::iterator it = m_Map.begin(); it != m_Map.end(); it++ )
    {
        if ( it.value().m_nodeIP.compare(strKey) == 0 )
        {
            // qDebug() << strKey << ", " << it.value().m_DisplayState;
            it.value().m_DisplayState = b;
            it.value().m_NeedUpdate = true;
            //this->m_Ready = true; // ?瑁?蝯?
            //return true;
        } // if
    } // for

    //this->m_Ready = true; // ?瑁?蝯?
    return true;
}
