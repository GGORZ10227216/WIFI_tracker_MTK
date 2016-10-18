#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <QThread>
#include <gldrawer.h>
#include <opencv2/opencv.hpp>

class dataTransfer : public QThread {
    Q_OBJECT

public:
    dataTransfer( cv::VideoCapture * srcCam, GLDrawer *srcDrawer ) ;
    ~dataTransfer() ;
    bool stopped = false ;

protected:
    void run();

private:
    cv::VideoCapture * sc ;
    cv::Mat fBuffer ;
    GLDrawer * sd ;
};

#endif // DATATRANSFER_H
