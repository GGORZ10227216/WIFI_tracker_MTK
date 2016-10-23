#ifndef GLOBALVARIABLE_H
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
    QString strKeyword;
    DeviceData* selectedToRecord;
    QString selectedNodeIPToRecord;
};

#endif // GLOBALVARIABLE_H
