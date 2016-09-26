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

    void run();
    qint64 readLineEx( char* chBuf, int iMaxLen);
signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // NODETHREAD_H
