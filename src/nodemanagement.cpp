#include <header/nodemanagement.h>

NodeManger::NodeManger(QObject *parent) : QTcpServer(parent) {
    /*
    connect( &server_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(tcpError(QAbstractSocket::SocketError)) );
    connect( &server_socket, SIGNAL(readyRead()),
             this, SLOT(tcpReady()) );
    */
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

void NodeManger::connectSever(QString strIP, int port, QString strMac, int intChannel)
{
    NodeThread* nt = new NodeThread(strIP, strMac, intChannel, this );
    connect(nt, SIGNAL(finished()), nt, SLOT(deleteLater()));
    nt->start();

    m_Map[strIP] = nt;
    //client_socket.abort();
    //client_socket.connectToHost(strIP, port);
    //connect( client_socket, SIGNAL(readyRead()), this, SLOT(readMessage()), Qt::DirectConnection);
    //NodeThread *thread = new NodeThread( m_NumOfConnect++, this);
    //connect( client_socket, SIGNAL(readyRead()), thread, SLOT(readMessage()));
    //connect(client_socket, SIGNAL(finished()), thread, SLOT(deleteLater()));
    //thread->start();
}

void NodeManger::readMessage()
{

}

void NodeManger::sendMessage(QString strIP, QString strInstruction)
{
    QMap<QString, NodeThread*>::iterator it = m_Map.find(strIP);
    //qDebug() << it.value()->m_intChannel;
    if ( !it.value()->sendMessage(strInstruction) )
        qDebug() << "no connect";
}
