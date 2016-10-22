#include "webv.h"
#include "ui_webv.h"

#include <QInputDialog>


webV::webV(QUrl src, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::webV)
{
    ui->setupUi(this);

    //this->setSizeGripEnabled(false);

    if ( src.isEmpty())
        return;

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->widget);
    ui->widget->setMediaPlayer( _player );
    _media = new VlcMedia( src.url(), _instance);

    QString titleName = "View_" ;
    titleName += src.url() ;
    this->setWindowTitle( titleName ) ;
    _player->open( _media );
    _player->play();
}

void webV::ChangeSrc( QUrl src ) {
    VlcMedia * tempM = _media ;
    _media = new VlcMedia( src.url(), _instance ) ;
    _player->open( _media );
    delete tempM ;
}

void webV::StartRecord( const char* fileName ) {
    std::stringstream titleCast ;
    titleCast << "title=" << fileName ;

    QStringList args ;
    args << "-f" << "gdigrab" << "-framerate"
         << fps.c_str() << "-i" << titleCast.str().c_str()
         << "-vcodec" << codec.c_str()
         << "-b" << bitrate.c_str() << fileName  ;
    qDebug() << args ;

    ffmpeg.start( "ffmpeg", args );
}

void webV::StopRecord() {
    qDebug() << "Stop REC!!" ;
    ffmpeg.open() ;
    if ( ffmpeg.isWritable() ) {
        ffmpeg.write( "q\r\n" ) ;
    } // if
    else {
        qDebug() << "YEE" ;
    } // else
}

void webV::closeEvent( QCloseEvent *bar ) {
    delete this ;
}

void webV::mouseDoubleClickEvent(QMouseEvent * event) {
    if ( !isRec ) {
        StartRecord( "test.mp4" );
        isRec = true ;
    } else {
        StopRecord() ;
        isRec = false ;
    } // if-else
}

void webV::mousePressEvent(QMouseEvent * event) {
    qDebug() << event->button() ;
    if ( event->button() == 2 ) {
        this->ChangeSrc( QUrl( "http://192.168.1.2:8080/?action=stream" ) );
    } // if
    else if ( event->button() == 1 ) {
        this->ChangeSrc( QUrl( "http://192.168.1.4:8080/?action=stream" ) );
    } // else if
}

webV::~webV()
{
    _player->stop() ;
    delete _player;
    delete _media;
    delete _instance;
    delete ui;
}
