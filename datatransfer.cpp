#include "datatransfer.h"

dataTransfer::dataTransfer( cv::VideoCapture * srcCam, GLDrawer *srcDrawer ) {
    sc = srcCam ;
    sd = srcDrawer ;
}

void dataTransfer::run() {
    while ( !stopped ) {
        *sc >> fBuffer ;
        sd->surface = QImage((uchar*) fBuffer.data, fBuffer.cols, fBuffer.rows, fBuffer.step, QImage::Format_RGB888);
        sd->update() ;
    } // while

    qDebug() << "quit" ;
}

dataTransfer::~dataTransfer() {
    qDebug() << "dd" ;
}
