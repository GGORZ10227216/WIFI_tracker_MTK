#ifndef DEVICEITEM_H
#define DEVICEITEM_H

#include <QList>
#include <QVariant>

//! [0]
class DeviceItem
{
public:
    explicit DeviceItem(const QList<QVariant> &data, DeviceItem *parentItem = 0);
    ~DeviceItem();

    void appendChild(DeviceItem *child);

    DeviceItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    DeviceItem *parentItem();


private:
    QList<DeviceItem*> m_childItems;
    QList<QVariant> m_itemData;
    DeviceItem *m_parentItem;
};
//! [0]

#endif // DEVICEITEM_H
