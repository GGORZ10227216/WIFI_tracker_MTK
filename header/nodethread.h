#ifndef NODETHREAD_H
#define NODETHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

struct Server
{
    QString strIp;
    QString strMac;
    int intChannel;
};

class NodeThread : public QThread
{
    Q_OBJECT
public:
    explicit NodeThread(qintptr ID, QObject *parent = 0);
    explicit NodeThread(QString in_StrIP, QString strMac, int intChannel, QObject *parent = 0);
    void run();

    bool sendMessage(QString strInstruction);
    qint64 readLineEx( char* chBuf, int iMaxLen);
signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

    void readyReceive();
    void startTransfer();
    void getErrorCode(QAbstractSocket::SocketError errorCode);
    void connectToServer();
    void endThread();
private:
    QTcpSocket *socket;
    QTcpSocket socket_Send;
    qintptr socketDescriptor;
    QString m_StrIP; // 蝭暺P
    QString m_StrMac; // ?箏?衽AC
    int m_intChannel; // ?箏?軏hannel
    int m_Port;
};

#endif // NODETHREAD_H
