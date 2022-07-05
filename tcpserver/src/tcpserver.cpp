#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{

}

void TcpServer::start(quint16 port)
{
    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }
}

void TcpServer::emitNewConnection(QString address, int port, int socId)
{
    Client client;
    client.setIp(address);
    client.setPort(port);
    client.setSocId(socId);
    emit(newconnection(client));
}

 void TcpServer::slotDisconnected(qintptr id)
{
    mapThreads.remove(id);
    emit(sigDisconnected(id));
}

void TcpServer::disconnectClientById(qintptr id)
{
    emit(closeSocket(id));
}


// This function is called by QTcpServer when a new connection is available.
void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    TcpThread *thread = new TcpThread(socketDescriptor);

    // connect signals/slots
    // once a thread is not needed, it will be beleted later
//    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    QThread *tmp = new QThread();
    thread->moveToThread(tmp);


    connect(tmp, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(tmp, SIGNAL(started()), thread, SLOT(loop()));
    tmp->start();
    tmp->sleep(1);
//    thread->start();
//    thread->sleep(1);

    emitNewConnection(thread->getAddress(),thread->getPort(), socketDescriptor);

    connect(thread, SIGNAL(newMessage(qintptr,QByteArray)), this, SIGNAL(newMessage(qintptr, QByteArray)), Qt::DirectConnection);
    connect(thread, SIGNAL(sigDisconnected(qintptr)), this, SLOT(slotDisconnected(qintptr)), Qt::DirectConnection);
    connect(this, SIGNAL(closeSocket(int)), thread, SLOT(closeSocket(int)), Qt::QueuedConnection);
//    listThreads.push_back(tmp);
    mapThreads.insert(socketDescriptor,tmp);
}
