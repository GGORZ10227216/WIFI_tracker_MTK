#ifndef NODEMANAGEMENT_H
#define NODEMANAGEMENT_H

#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>
#include <header/nodethread.h>

class NodeManger : public QTcpServer {
    Q_OBJECT
public:
    explicit NodeManger(QObject *parent = 0);
    ~NodeManger();
    QTcpSocket server_socket;
public slots:
    void tcpReady();
    void tcpError( QAbstractSocket::SocketError error );
    bool start_listen(int port_no);
protected:
    void incomingConnection(qintptr descriptor );
};

#endif // NODEMANAGEMENT_H
