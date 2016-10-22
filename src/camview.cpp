#include <header/camview.h>
#include "ui_camview.h"

camView::camView( std::string url, std::string port, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::camView)
{
    ui->setupUi(this);
    ui->openGLWidget->show() ;
    u = url ;
    p = port ;
    StartCapture();
}

void camView::StartCapture() {
    dt = new dataTransfer( &cap, this->ui->openGLWidget, u, p ) ;
    dt->start();
}

void camView::closeEvent( QCloseEvent *bar ) {

    dt->stopped = true ;
    while ( !dt->isFinished() ) ;

    delete dt ;
    delete ui;

    cap.release();
    qDebug() << "GL window close." ;
    bar->accept();
}
