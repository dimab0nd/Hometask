#ifndef CLIENT_H
#define CLIENT_H
#include <QString>

//client class only for tableview
class Client
{

public:
    Client();
    QString getIp() const;
    void setIp(const QString &value);


    QString getHost() const;
    void setHost(const QString &value);

    QString getLast_msg() const;
    void setLast_msg(const QString &value);

    int getPort() const;
    void setPort(int value);

    int getSocId() const;
    void setSocId(int value);

private:
    QString ip;
    int port;
    QString host;
    QString last_msg;
    int socId;

};

#endif // CLIENT_H
