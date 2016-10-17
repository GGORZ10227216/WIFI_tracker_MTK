#include <ui/camview.h>
#include "ui_camview.h"

camView::camView(QString url, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::camView)
{
    ui->setupUi(this);
    // ui->openGLWidget->paintGL();
    ui->openGLWidget->show() ;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), ui->openGLWidget, SLOT(update()));
    timer->start(42);

}

camView::~camView()
{
    delete ui;
}
