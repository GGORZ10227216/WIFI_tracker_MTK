﻿#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include "header/devicemap.h"
#include "header/client/areadata.h"
#include "header/nodemanagement.h"
#include <atomic>
#include <thread>
struct GlobalV
{
    DeviceMap deviceMap;
    AreaData areaData;
    NodeManger n_mana;
    int selectedNodeState;
    int updateNewestNumber;
    QString strKeyword;
    DeviceData* selectedToRecord;
    QString selectedNodeIPToRecord;
    QList<Server> needReConnect;
    QMap<QString, QString> nodeMacMap; // Node Mac -> location
    QMap<QString, QString> nodeIp2AreaMap; // Node Ip -> location
};

#endif // GLOBALVARIABLE_H
