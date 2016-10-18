#include "header/mainwindow.h"
#include <header/nodemanagement.h>
#include "header/globalvariable.h"
#include <QApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QtPlugin>

extern GlobalV Global;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //n_mana->connectSever("192.168.1.3", 48763, "F0:79:59:D1:71:D4", 6 );
    //n_mana->sendMessage( "192.168.1.2", "456");
    //n_mana->start_listen( 25300 ) ;
    //NodeThread* nt = new NodeThread("192.168.1.2", 13768);
   // nt->start();
    return a.exec();
}
