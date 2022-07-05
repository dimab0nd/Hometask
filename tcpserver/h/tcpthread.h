#ifndef TCPTHREAD_H
#define TCPTHREAD_H
#include <QThread>
#include <QTcpSocket>

class TcpThread : public QObject
{
    Q_OBJECT
public:
    explicit TcpThread(qintptr id);
    QString getAddress() const;
    int getPort() const;
    qintptr getSocId() const;
    QTcpSocket *getSocket() const;

signals:
    void newMessage(qintptr,QByteArray);
    void sigDisconnected(qintptr);

public slots:
    void readyRead();
    void disconnected();
    void closeSocket(int id);
    void loop();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // TCPTHREAD_H
