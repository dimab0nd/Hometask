#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpServer>
#include "client.h"
#include "tcpthread.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = 0);
    void start(quint16 port = 1234);
    void emitNewConnection(QString address, int port, int socId);

signals:
    void newconnection(Client);
    void newMessage(qintptr, QByteArray);
    void sigDisconnected(qintptr);
    void closeSocket(int);

public slots:
    void slotDisconnected(qintptr id);
    void disconnectClientById(qintptr id);
protected:
    void incomingConnection(qintptr handle) override;
private:
//    QList<QThread*> listThreads;
    QMap<int, QThread*> mapThreads;

};

#endif // TCPSERVER_H
