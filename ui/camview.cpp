#include <ui/camview.h>
#include "ui_camview.h"

camView::camView(QString url, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::camView)
{
    ui->setupUi(this);
    ui->openGLWidget->show() ;

    StartCapture();
}

void camView::StartCapture() {
    cap.open( 0 ) ;

    if ( cap.isOpened() ) {
        dt = new dataTransfer( &cap, this->ui->openGLWidget ) ;
        dt->start();
    } // if
    else {
        qDebug() << "GG" ;
    } // else
}

void camView::closeEvent( QCloseEvent *bar ) {

    dt->stopped = true ;
    while ( !dt->isFinished() ) ;

    delete dt ;
    delete ui;
    cap.release() ;

    qDebug() << "GL window close." ;
    bar->accept();
}
