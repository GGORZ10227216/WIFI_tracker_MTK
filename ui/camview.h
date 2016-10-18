#ifndef CAMVIEW_H
#define CAMVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <gldrawer.h>
#include <opencv2/opencv.hpp>
#include <datatransfer.h>
#include <QCloseEvent>

namespace Ui {
class camView;
}

class camView : public QMainWindow
{
    Q_OBJECT

public:
    explicit camView(QString url , QWidget *parent = 0);

protected:
    cv::VideoCapture cap ;

private:
    Ui::camView *ui;
    dataTransfer * dt = NULL ;
    void StartCapture() ;
    void closeEvent(QCloseEvent *bar) ;
};

#endif // CAMVIEW_H
