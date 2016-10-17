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
    // is client
    void connectSever(QString strIP, int port, QString strMac, int intChannel);
    void readMessage();
    void sendMessage( QString strIP, QString strInstruction );
    // end
    ~NodeManger();

    QTcpSocket server_socket;
    QTcpSocket client_socket;
public slots:
    void tcpReady();
    void tcpError( QAbstractSocket::SocketError error );
    bool start_listen(int port_no);
protected:
    void incomingConnection(qintptr descriptor );
private:
    int m_NumOfConnect = 0;
    QMap<QString, NodeThread*> m_Map;
};

/*
class NodeManger_Client : public QTcpSocket
{

};*/

#endif // NODEMANAGEMENT_H
