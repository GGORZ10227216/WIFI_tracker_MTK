#ifndef WEBV_H
#define WEBV_H

#include <QWidget>
#include <QWebEngineView>
#include <QProcess>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/Enums.h>
#include <string>
#include <sstream>
#include <iostream>
#include <QMouseEvent>

namespace Ui {
class webV;
}

class webV : public QWidget
{
    Q_OBJECT

public:
    explicit webV( QUrl src,QWidget *parent = 0);
    void ChangeSrc( QUrl src ) ;
    void StartRecord( const char *fileName ) ;
    void StopRecord() ;
    ~webV();
    std::string fps = "24", bitrate = "300000" ;
    std::string codec = "libx264" ;

private:
    Ui::webV *ui;
    VlcInstance * _instance ;
    VlcMediaPlayer * _player ;
    VlcMedia * _media ;
    std::string windowID = "Form" ;
    bool isRec = false ;
    void closeEvent(QCloseEvent *bar) ;
    void mouseDoubleClickEvent(QMouseEvent * event) ;
    void mousePressEvent(QMouseEvent * event) ;
    QProcess ffmpeg ;
};

#endif // WEBV_H
