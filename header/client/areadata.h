#ifndef AREADATA_H
#define AREADATA_H
#include "header/mainwindow.h"
#include "header/client/machine.h"

struct MapSize
{
    int bass;
    int machine;
};

class AreaData
{
public:
    AreaData();
    ~AreaData();
    bool read(const QString fileName);
    QString toString();

private:
    QString m_Location;
    MapSize m_MapSize;
    QList<Machine> m_MachineList;
};
#endif // AREADATA_H
