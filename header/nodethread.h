#ifndef NODETHREAD_H
#define NODETHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>


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

    void connectToServer();

private:
    QTcpSocket *socket;
    QTcpSocket socket_Send;
    qintptr socketDescriptor;
    QString m_StrIP; // 節點IP
    QString m_StrMac; // 基地台MAC
    int m_intChannel; // 基地台channel
    int m_Port;
};

#endif // NODETHREAD_H
