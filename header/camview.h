#ifndef CAMVIEW_H
#define CAMVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <header/gldrawer.h>
#include <opencv2/opencv.hpp>
#include <header/videoprocessor.h>
#include <QCloseEvent>

namespace Ui {
class camView;
}

class camView : public QMainWindow
{
    Q_OBJECT

public:
    explicit camView( std::string url, std::string port, QWidget *parent = 0 );

protected:
    cv::VideoCapture cap ;

private:
    Ui::camView *ui;
    dataTransfer * dt = NULL ;
    std::string u, p ;
    void StartCapture() ;
    void closeEvent(QCloseEvent *bar) ;
};

#endif // CAMVIEW_H
