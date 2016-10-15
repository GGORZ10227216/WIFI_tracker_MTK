#include <ui/camview.h>
#include "ui_camview.h"

camView::camView(QString url, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::camView)
{
    ui->setupUi(this);
    ui->cam->setUrl( QUrl( url ) );
    ui->cam->show() ;
}

camView::~camView()
{
    delete ui;
}
