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
#include <header/devicedata.h>
#include <string>
#include <sstream>
#include <iostream>
#include <QMouseEvent>

class DeviceData;
namespace Ui {
class webV;
}


class webV : public QWidget
{
    Q_OBJECT

public:
    explicit webV(QUrl src, DeviceData *dData, QString fileName, QWidget *parent = 0);
    void ChangeSrc( QUrl src ) ;
    void StartRecord( const char *fileName ) ;
    void StopRecord() ;
    bool isRecording(){ return isRec; }
    ~webV();
    std::string fps = "24", bitrate = "300000" ;
    std::string codec = "libx264" ;
    bool isWatching = false;

private:
    QString m_strTitle;
    QString m_strfileName;
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
