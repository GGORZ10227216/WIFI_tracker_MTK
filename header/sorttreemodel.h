#ifndef SORTTREEMODEL_H
#define SORTTREEMODEL_H

#include <header/treemodel.h>
#include <QSortFilterProxyModel>
#include <QFile>
#include <QDebug>
#include <QObject>
#include <QTreeView>

class SortTreeView {
public:
    TreeModel * srcModel ;
    QSortFilterProxyModel * model ;
    QTreeView *view ;

    SortTreeView( QTreeView * tarView, QByteArray data, QStringList headers ) ;
    void insertChild();
    bool insertColumn();
    void insertRow();
    bool removeColumn();
    void removeRow();

    QModelIndexList search( QString target ) ;
    void searchRemove( QString target ) ;
    void searchEdit(QString target , int col = 1 ) ;
    void updateActions() ; // Useless for now......
};

#endif // SORTTREEMODEL_H
