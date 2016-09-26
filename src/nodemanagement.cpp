#include <header/nodemanagement.h>

NodeManger::NodeManger(QObject *parent) : QTcpServer(parent) {
    server_socket.setSocketOption(QAbstractSocket::KeepAliveOption, true );
}

NodeManger::~NodeManger() {
    server_socket.disconnectFromHost();
    server_socket.waitForDisconnected();
}

void NodeManger::tcpReady() {
    QByteArray array = server_socket.read(server_socket.bytesAvailable());
    qDebug() << array ;
}

void NodeManger::tcpError(QAbstractSocket::SocketError error) {
    QMessageBox::warning( (QWidget *)this->parent(), tr("Error"),tr("TCP error: %1").arg( server_socket.errorString() ) );
}

bool NodeManger::start_listen(int port_no) {
    if( !this->listen( QHostAddress::Any, port_no ) ) {
        QMessageBox::warning( (QWidget *)this->parent(), tr("Error!"), tr("Cannot listen to port %1").arg(port_no) );
    }
    else
        return true;
}

void NodeManger::incomingConnection(qintptr descriptor) {
    // We have a new connection
    qDebug() << descriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    NodeThread *thread = new NodeThread( descriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
