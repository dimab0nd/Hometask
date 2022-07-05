#include "tcpthread.h"
#include <QHostAddress>

TcpThread::TcpThread(qintptr id)
{
    this->socketDescriptor = id;

}

void TcpThread::loop()
{
    qDebug() << " Thread started";
    socket = new QTcpSocket();

    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // TODO: emit error signal
        // something's wrong, we just emit a signal
        //        emit error(socket->error());
        return;
    }


    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
//    connect(this, SIGNAL(finished()), socket, SLOT(close()));
    qDebug() << socketDescriptor << " Client connected";

}

QString TcpThread::getAddress() const
{
    if(socket)
    {
        return socket->peerAddress().toString();
    }
    else
        return "";

}

int TcpThread::getPort() const
{
    if(socket)
    {
        return socket->localPort();
    }
    else
        return 0;
}

qintptr TcpThread::getSocId() const
{
    if(socket)
    {
        return socketDescriptor;
    }
    else
        return 0;
}
void TcpThread::readyRead()
{
    QByteArray data = socket->readAll();

    qDebug() << socketDescriptor << " Data in: " << data;
    emit(newMessage(socketDescriptor, data));
}

void TcpThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    emit(sigDisconnected(socketDescriptor));

//    exit(0);
}

void TcpThread::closeSocket(int id)
{
    if(socketDescriptor == id) socket->close();
}

QTcpSocket *TcpThread::getSocket() const
{
    return socket;
}
