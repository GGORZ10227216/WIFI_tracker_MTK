#include "header/videoprocessor.h"

dataTransfer::dataTransfer( cv::VideoCapture * srcCam, GLDrawer *srcDrawer,
                            std::string cs, std::string p ) {
    sc = srcCam ;
    sd = srcDrawer ;
    camSrc = cs ;
    port = p ;
}

void dataTransfer::run() {
    bool init = false ;
    QProcess ffmpeg ;
    std::stringstream ss ;
    ss << camSrc << ':' << port << "/?action=stream?dummy=a.mjpg" ;

    sc->open( ss.str().c_str() ) ;

    QDateTime time = QDateTime::currentDateTime() ;

    std::string fileSrc = camSrc;
    fileSrc.erase( 0,7 ) ;
    for ( int i = 0 ; i < fileSrc.size() ; ++ i ) {
        if ( fileSrc.at( i ) == '.' )
            fileSrc.at( i ) = '_' ;
    } // for

    std::stringstream ss2 ;
    ss2 << fileSrc << '_' << time.toString( "yyyy-MM-dd_hh_mm_ss" ).toStdString() << ".avi" ;
    dstFileName = ss2.str().c_str() ;
    QStringList args ;
    args << "-f" << "mjpeg" /*<< "-r"
         << srcFps.c_str() <<*/ << "-i" << ss.str().c_str()
         << "-vcodec" << codec.c_str() << "-b"
         << bitrate.c_str() /*<< "-r" << dstFps.c_str()*/
         << dstFileName.c_str();

    qDebug() << args ;
    // ffmpeg.startDetached( "ffmpeg", args ) ;
    qDebug() << ffmpeg.pid() ;
    while ( !stopped ) {
        *sc >> fBuffer ;
        if ( !init ) {
            init = true ;
        } // if

        sd->surface = QImage((uchar*) fBuffer.data, fBuffer.cols,
                             fBuffer.rows, fBuffer.step,
                             QImage::Format_RGB888);
        sd->update() ;
    } // while

    qDebug() << "quit" ;
}

dataTransfer::~dataTransfer() {
    qDebug() << "dd" ;
    fBuffer.release(); 
}
