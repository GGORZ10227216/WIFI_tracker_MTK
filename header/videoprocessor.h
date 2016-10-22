#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <QThread>
#include <QProcess>
#include <QDateTime>
#include <header/gldrawer.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>
#include <QStringList>
#include <cstdlib>

class dataTransfer : public QThread {
    Q_OBJECT

public:
    dataTransfer(cv::VideoCapture * srcCam, GLDrawer *srcDrawer , std::string cs, std::string p) ;
    ~dataTransfer() ;
    bool stopped = false ;

protected:
    void run();

private:
    std::string camSrc, port ;
    cv::VideoCapture * sc ;
    cv::Mat fBuffer ;
    GLDrawer * sd ;
    std::string srcFps = "24", dstFps = "24", bitrate = "300000" ;
    std::string codec = "mpeg4",dstFileName ;

};

#endif // DATATRANSFER_H
