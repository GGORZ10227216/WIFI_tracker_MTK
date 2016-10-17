#ifndef AREADATA_H
#define AREADATA_H
#include "header/mainwindow.h"
#include "header/client/machine.h"
#include <ui_mainwindow.h>
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
    void update2View( QTableWidget* tView );
    void getAllNodes();
    void getNodeCoord( QString strIP, QList<Coordinate>& coordList );

    /*void getCoordnateByLocation( QString strLocation )
    {
        getAllNodes();
        for (  )
    }*/

private:
    QString m_Location;
    MapSize m_MapSize;
    QList<Machine> m_MachineList;
    QList<NodeData> m_NodeList; // all nodes it has
};
#endif // AREADATA_H
