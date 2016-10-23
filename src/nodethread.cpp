#include <header/tree/sorttreemodel.h>
#include "header/nodethread.h"
#include "header/devicemap.h"
#include <header/globalvariable.h>
extern GlobalV Global;

NodeThread::NodeThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

NodeThread::NodeThread(QString in_StrIP, QString in_StrMac, int in_IntChannel, QObject *parent) :
    QThread(parent)
{

    m_StrIP = in_StrIP;
    // m_Port = in_Port;
    m_StrMac = in_StrMac;
    m_intChannel = in_IntChannel;
    socket = new QTcpSocket();
    socket_Send.connectToHost(m_StrIP, 48763); // send msg to server
    socket->connectToHost(m_StrIP, 13768);

}

void NodeThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    if ( socket == NULL ) // be a server
    {
        socket = new QTcpSocket();
        // set the ID
        if(!socket->setSocketDescriptor(this->socketDescriptor))
        {
            // something's wrong, we just emit a signal
            emit error(socket->error());
            return;
        } // if

        // We'll have multiple clients, we want to know which is which
        qDebug() << socketDescriptor << " Client connected";
    } // if
    else// be a client
    {
       /* if ( socket_Send.state() != QTcpSocket::ConnectedState  )
        {
            emit error(socket->error());
            return;
        }*/

        //socket_Send.waitForConnected();
        QByteArray barr = (this->m_StrMac + "," + QString::number(this->m_intChannel)).toUtf8();
        socket_Send.write(barr);
        /*if ( socket_Send.state() == QTcpSocket::ConnectedState  )
        {

        } // if*/

    } // else



    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies
    this->exec();
}

void NodeThread::readyReceive()
{
    qDebug() << "readyReceive";
    socket->abort();
    socket->connectToHost(m_StrIP, 13768);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

}

void NodeThread::connectToServer()
{
    //socket->connectToHost(m_StrIP, send_Port);
    qDebug() << "connecttoserver";
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReceive()), Qt::DirectConnection);

}

qint64 NodeThread::readLineEx( char* chBuf, int iMaxLen)
{
    static qint64 totalLen = 0;
    char ch = '\0';
    socket->getChar(&ch);
    chBuf[totalLen++] = ch;
    if ( ch == '\r' ) // telnet /r/n
    {
        socket->getChar(&ch);
        chBuf[totalLen++] = ch;
    } // if

    if ( totalLen == iMaxLen - 2 || ch == '\n' ) // can't read anymore or \n
    {
        qint64 ret = totalLen;
        chBuf[totalLen] = '\0';
        totalLen = 0;
        return ret; // return total length
    } // if


    return readLineEx( chBuf, iMaxLen); // not end so return -1
}

bool setReceiveDataFormat(QString& input)
{
    input = input.replace(" ", ",");
    input = input.replace("-", "");
    return true;
}

void NodeThread::readyRead()
{
    //qDebug() << " Data in: \n" << socket->readAll() << "\n-----------------------------------------------------------------";
    //return ;
    QString read_All = socket->readAll();
    if ( read_All.size() <= 0 ) return;
    QStringList strList = read_All.split("\n");
    socket->write("success\r\n");
    for ( int i = 0; i < strList.size(); i++ )
    {
        if ( strList[i].size() <= 0 ) continue;
        //qDebug() << strList[i];
        QString str = strList[i].replace("\n", "");
        if ( str.split(",").size() != DeviceData::getColumnCount() )
            continue;
        if ( i == 0 && str.size() < 17 )
            continue;
        DeviceData dData( m_StrIP, str  );
        //if ( dData.m_Db < -70 ) return;
        //dData.m_nodeIP = m_StrIP;
        Global.deviceMap.updateData(dData);// or [dData.getMac()] = dData;
    } // for
    //

}

void NodeThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}

 bool NodeThread::sendMessage( QString strInstruction )
 {
     if ( this->socket_Send.state() != QTcpSocket::ConnectedState )
         return false;
    QByteArray barr = strInstruction.toUtf8();
    this->socket_Send.write(barr);
    return true;
 }
