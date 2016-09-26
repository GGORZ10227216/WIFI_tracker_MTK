#include "header/devicedata.h"
#include "header/devicemap.h"
#include "header/nodethread.h"
extern DeviceMap gDeviceMap;

NodeThread::NodeThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;

}

void NodeThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
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

    return -1; // not end so return -1
}


void NodeThread::readyRead()
{
    // get the information
    static char buf[64];

    qint64 len = readLineEx( buf, 64 );
    // will write on server side window
    socket->write("success\r\n");
    if ( len == -1 ) return;
    qDebug() << QThread::currentThreadId() << " " << socketDescriptor << " Data in: " << buf;
    DeviceData dData(  buf );
    gDeviceMap.updateData(dData);// or [dData.getMac()] = dData;
    memset( buf, '\0', 64 );
    //

}

void NodeThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}
