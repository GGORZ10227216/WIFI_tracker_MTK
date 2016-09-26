#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <QModelIndex>
#include <QVariant>
#include <QTreeView>

class DeviceItem;

//! [0]
class DeviceList : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit DeviceList(const QString &data, QTreeView * dt, QObject *parent = 0);
    ~DeviceList();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE ;
    bool addData(QList<QVariant> columnData);
    QSortFilterProxyModel * qSftm = NULL ;
private:
    void setupModelData(const QStringList &lines, DeviceItem *parent);
    QTreeView * displayTarget = NULL ;
    DeviceItem *rootItem;
};
//! [0]

#endif // DEVICELIST_H
