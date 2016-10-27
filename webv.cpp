#include "webv.h"
#include "ui_webv.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QString>
webV::webV(QUrl src, DeviceData *dData, QString fileName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::webV)
{
    ui->setupUi(this);
    std::stringstream ss ;
    ss << dData->m_nodeIP.toStdString()
       << " (" << dData->m_Location.toStdString() << ")" ;

    _d = dData ;
    ui->Info->setText( QString( ss.str().c_str() ) );
    ui->Info->setTextFormat( Qt::AutoText ) ;
    //this->setSizeGripEnabled(false);
    qDebug() << "------------";
    if ( src.isEmpty())
        return;

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->widget);
    ui->widget->setMediaPlayer( _player );
    _media = new VlcMedia( src.url(), _instance);

    QString titleName = "View_" ;
    titleName += fileName ;
    this->setWindowTitle( titleName ) ;
    m_strTitle = titleName;
    m_strfileName = fileName + ".mp4";
    _player->open( _media );
    _player->play();
    isRec = false;
}

void webV::ChangeSrc( QUrl src ) {
    VlcMedia * tempM = _media ;
    _media = new VlcMedia( src.url(), _instance ) ;
    _player->open( _media );
    delete tempM ;

    std::stringstream ss ;
    ss << _d->m_nodeIP.toStdString()
       << " (" << _d->m_Location.toStdString() << ")" ;

    ui->Info->setText( QString( ss.str().c_str() ) );
    ui->Info->setTextFormat( Qt::AutoText ) ;
}

void webV::StartRecord( const char* fileName ) {
    isRec = true;
    std::stringstream titleCast ;
    titleCast << "title=" << m_strTitle.toLatin1().data() ;

    QStringList args ;

    args << "-f" << "gdigrab" << "-framerate"
         << fps.c_str() << "-i" << titleCast.str().c_str()
         << "-vcodec" << codec.c_str()
         << "-b" << bitrate.c_str() << "-draw_mouse"
         << "0" << fileName  ;

    qDebug() << args ;

    ffmpeg.start( "ffmpeg", args );
}

void webV::StopRecord() {
    isRec = false;
    QString ss = m_strTitle + "Stop REC!!";
    QMessageBox::information(0, QString::fromLocal8Bit("Warning"), ss);
    //QMessageBox::information(0, "警告", "此裝置已結束錄像");
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
    qDebug() << "close````````````````";
    if (isRec)
        StopRecord();

    else  qDebug() << "WTF no REC!!" ;
    this->isWatching = false;


    // delete this ;
}

void webV::mouseDoubleClickEvent(QMouseEvent * event) {
    if ( !isRec ) {
        StartRecord( "test.mp4" );
    } else {
        StopRecord() ;
    } // if-else
}

void webV::mousePressEvent(QMouseEvent * event) {
    qDebug() << event->button() ;
    if ( event->button() == 2 ) {
        this->ChangeSrc( QUrl( "http://192.168.1.2:8080/?action=stream" ) );
    } // if
    else if ( event->button() == 1 ) {
        //this->ChangeSrc( QUrl( "http://192.168.1.4:8080/?action=stream" ) );
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

