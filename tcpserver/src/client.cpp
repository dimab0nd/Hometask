#include "client.h"

Client::Client()
{

}

QString Client::getIp() const
{
    return ip;
}

void Client::setIp(const QString &value)
{
    ip = value;
}

QString Client::getHost() const
{
    return host;
}

void Client::setHost(const QString &value)
{
    host = value;
}

QString Client::getLast_msg() const
{
    return last_msg;
}

void Client::setLast_msg(const QString &value)
{
    last_msg = value;
}

int Client::getPort() const
{
    return port;
}

void Client::setPort(int value)
{
    port = value;
}

int Client::getSocId() const
{
    return socId;
}

void Client::setSocId(int value)
{
    socId = value;
}
