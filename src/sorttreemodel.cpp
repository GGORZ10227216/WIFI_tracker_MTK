#include <header/sorttreemodel.h>

SortTreeView::SortTreeView( QTreeView * tarView, QByteArray data, QStringList headers ) {
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

void SortTreeView::insertRow()
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

void SortTreeView::searchEdit( QString target, int col ) {
    QModelIndexList index = search( target ) ;
    if ( !index.empty() ) {
        qDebug() << model->index( index.at(0).row(),
                                  index.at(0).column() + col ).data() ;
        model->setData( model->index( index.at(0).row(),
                                      index.at(0).column() + col ),
                        "GGININDER" ) ;
    } // if
} // SortTreeView::searchEdit()
