#ifndef SORTTREEMODEL_H
#define SORTTREEMODEL_H

#include <header/tree/treemodel.h>
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

    SortTreeView(QTreeView * tarView, QString data, QStringList headers ) ;
    void insertChild();
    bool insertColumn();
    void insertRow();
    void insertRow(QStringList dataList);
    bool removeColumn();
    void removeRow();

    QModelIndexList search( QString target ) ;
    void searchRemove( QString target ) ;
    bool searchEdit(QString target , int col = 1, QVariant newValue = "no init" ) ;
    bool checkDataIsExist( QString target );
    void updateActions() ; // Useless for now......
    void update(QString keyword); // update view per second
    void updateClient();
};

#endif // SORTTREEMODEL_H
