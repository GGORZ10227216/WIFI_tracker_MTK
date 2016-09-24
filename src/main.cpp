#include "header/mainwindow.h"
#include <header/nodemanagement.h>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    NodeManger * n_mana = new NodeManger() ;

    n_mana->start_listen( 25300 ) ;
    return a.exec();
}
