#include <header/tree/sorttreemodel.h>
#include <header/devicemap.h>
#include <header/globalvariable.h>
extern GlobalV Global;

SortTreeView::SortTreeView( QTreeView * tarView, QString data, QStringList headers ) {
    srcModel = new TreeModel(headers, data);
    model = new QSortFilterProxyModel( this->srcModel ) ;
    model->setSourceModel( srcModel ) ;

    view = tarView ;
    view->setModel( model );
    view->setSortingEnabled( true ) ;
    model->sort( 0,Qt::SortOrder::AscendingOrder );
}

void SortTreeView::updateActions()
{
    /*
    bool hasSelection = !view->selectionModel()->selection().isEmpty();
    removeRowAction->setEnabled(hasSelection);
    removeColumnAction->setEnabled(hasSelection);

    bool hasCurrent = view->selectionModel()->currentIndex().isValid();
    insertRowAction->setEnabled(hasCurrent);
    insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        view->closePersistentEditor(view->selectionModel()->currentIndex());

        int row = view->selectionModel()->currentIndex().row();
        int column = view->selectionModel()->currentIndex().column();
        if (view->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
  */
}

void SortTreeView::insertChild()
{
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
    }

    view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool SortTreeView::insertColumn()
{
    QAbstractItemModel *model = view->model();
    int column = view->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

    updateActions();

    return changed;
}

/*void SortTreeView::insertRow()
{

    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();
    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();
    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }
}*/

void SortTreeView::insertRow()
{

    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();
    //qDebug()<< "1. " << srcModel->size() << endl;
    if (!model->insertRow( srcModel->size(), index.parent()))
        return;

    updateActions();
    //qDebug()<< "2. " << srcModel->size() << endl;
    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(srcModel->size()-1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }
}

void SortTreeView::insertRow( QStringList dataList )
{

    // QAbstractItemModel *model = view->model();

    if (!model->insertRow(  model->rowCount(), QModelIndex() ))
        return;

    updateActions();

    model->setData( model->index( model->rowCount() - 1,0), QVariant(dataList[0]));

    // view->model()->sort(0);
    QModelIndex tIndex = search(dataList[0]).at( 0 ) ;

    for (int column = 1; column < model->columnCount() ; ++column) {
        //QModelIndex child = model->index( model->rowCount()-1, column, QModelIndex());
        model->setData(model->index( tIndex.row(), tIndex.column() + column ), QVariant(dataList[column]));

    }
}

bool SortTreeView::removeColumn()
{
    QAbstractItemModel *model = view->model();
    int column = view->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    bool changed = model->removeColumn(column);

    if (changed)
        updateActions();

    return changed;
}

void SortTreeView::removeRow()
{

    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();

}

QModelIndexList SortTreeView::search( QString target ) {
    QAbstractItemModel *model = view->model();
    QModelIndexList result = view->model()->match(
                            model->index(0, 0),
                            Qt::DisplayRole,
                            QVariant::fromValue( target ),
                            2,
                            Qt::MatchRecursive);
    return result ;
}

void SortTreeView::searchRemove( QString target ) {    
    QModelIndexList index = search( target ) ;
    if ( !index.empty() && model->removeRow(index.at(0).row(), index.at(0).parent()))
         updateActions();
}

bool SortTreeView::searchEdit( QString target, int col, QVariant newValue ) {
    QModelIndexList index = search( target ) ;
    if ( !index.empty() ) {
        QString strNewValue = newValue.toString();
        /*qDebug() << model->index( index.at(0).row(),
                                  index.at(0).column() + col ).data() ;*/
        model->setData( model->index( index.at(0).row(),
                                      index.at(0).column() + col ),
                        strNewValue ) ;
        return true;
    } // if

    return false;
} // SortTreeView::searchEdit()

bool SortTreeView::checkDataIsExist( QString target ) {
    QModelIndexList index = search( target ) ;
    if ( !index.empty() )
         return true;
    return false;
}

/*void SortTreeView::update() {
    for ( qint64 i = 0; i < gDeviceMap.size(); i++ )
    {
        if ( gDeviceMap.At(i)->m_NeedUpdate )
        {
            gDeviceMap.At(i)->m_NeedUpdate = false; // been update
            if ( !searchEdit( gDeviceMap.At(i)->m_Mac, 1, gDeviceMap.At(i)->m_Db ) ) // data isn't exist then insert the data
                insertRow( gDeviceMap.At(i)->toStringList() );//gDeviceMap.At(i)->toStringList()

        } // if
    } // for
}*/


void SortTreeView::update(QString keyword) {

    //while ( !Global.deviceMap.m_Ready.load() )
    //    std::this_thread::yield(); // 霈cpu霈隞犖??

    Global.deviceMap.m_Ready = false; // 雿?deviceMap
    for ( qint64 i = 0; i < Global.deviceMap.size(); i++ )
    {
        //qDebug() << "-------------------------" << keyword;
        if ( keyword.size() > 0 &&  Global.deviceMap.At(i)->m_Mac.indexOf(keyword) == -1 ) continue;
        //else if (keyword.size() > 0) qDebug() << Global.deviceMap.At(i)->m_Mac.indexOf(keyword);
        /*if (  Global.deviceMap.At(i)->m_UpdateState < Global.updateNewestNumber )
        {
            searchRemove(Global.deviceMap.At(i)->m_Mac);
            Global.deviceMap.DeleteData(Global.deviceMap.At(i)->m_Mac);
        } // if
        else*/ if ( Global.deviceMap.At(i)->m_DisplayState == Global.selectedNodeState &&  // ?嗉???displaystate?lobal?詨????豢????＊蝷?
             Global.deviceMap.At(i)->m_NeedUpdate )
        {
            Global.deviceMap.At(i)->m_NeedUpdate = false; // been update
            if ( !checkDataIsExist(Global.deviceMap.At(i)->m_Mac) ) // data isn't exist then insert the data
            {
                if ( -70 <= Global.deviceMap.At(i)->m_Db && Global.deviceMap.At(i)->m_Db <= 0 )
                    insertRow( Global.deviceMap.At(i)->toStringList() );//gDeviceMap.At(i)->toStringList()
                else
                    Global.deviceMap.DeleteData(Global.deviceMap.At(i)->m_Mac);
            } // if
            else if( -70 <= Global.deviceMap.At(i)->m_Db && Global.deviceMap.At(i)->m_Db <= 0 )
            {
                searchEdit( Global.deviceMap.At(i)->m_Mac, 1, Global.deviceMap.At(i)->m_Db );
                searchEdit( Global.deviceMap.At(i)->m_Mac, 2, Global.deviceMap.At(i)->m_Frame );
            } // else if
            else // Db is zero then delete data
            {
                searchRemove(Global.deviceMap.At(i)->m_Mac);
                Global.deviceMap.DeleteData(Global.deviceMap.At(i)->m_Mac);
            } // else
        } // if
        else if ( Global.deviceMap.At(i)->m_DisplayState != Global.selectedNodeState )
        {
            Global.deviceMap.At(i)->m_NeedUpdate = false; // been update
            searchRemove(Global.deviceMap.At(i)->m_Mac);
        } // else
    } // for

    Global.deviceMap.m_Ready = true; // ?暸?deviceMap

}

void SortTreeView::updateClient()
{
    /*for ( int i = 0; i < Global.areaData.size(); i++ )
    {

    } // for*/
}
