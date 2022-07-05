#include "tablemodel.h"

tablemodel::tablemodel()
{
    headers_  << "id" << "IP"  << "Порт" << "Последнее сообщение";
}

QVariant tablemodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && section >= 0) {
        if (role == Qt::DisplayRole) { return headers_.at(section); }
    }
    return QVariant();
}

QVariant tablemodel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) { return QVariant(); }

    if(listClients_.isEmpty() || listClients_.size() <= index.row()) { return QVariant(); }

    int column = index.column();
    const Client client = listClients_.at(index.row());

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
        case 0:{ return client.getSocId(); }
        case 1:{ return client.getIp(); }
        case 2:{ return client.getPort(); }
        case 3:{ return client.getLast_msg(); }
        default:{}
        }
    }
    return QVariant();
}

bool tablemodel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role)
    {

    }
    return true;
}

Qt::ItemFlags tablemodel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);


    if(index.isValid())
    {
        return  Qt::ItemIsSelectable|Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    }
    else
        return Qt::NoItemFlags;

}

int tablemodel::rowCount(const QModelIndex &) const
{
    return listClients_.size();
}

int tablemodel::columnCount(const QModelIndex &) const
{
    return headers_.count();
}

qintptr tablemodel::getSocIdByRow(int row)
{
    if(row >= 0 && row < listClients_.size())
    {
        return listClients_[row].getSocId();
    }
    else {
        return 0;
    }
}




void tablemodel::slotNewConnection(Client client)
{
    listClients_.push_back(client);
    beginResetModel();
    endResetModel();

}

void tablemodel::slotDisconnected(qintptr id)
{
    for(int i = 0; i < listClients_.size(); ++i)
    {
        if(listClients_[i].getSocId() == id)
        {
            listClients_.removeAt(i);
            break;
        }
    }
    beginResetModel();
    endResetModel();
}

void tablemodel::slotNewMessage(qintptr id, QByteArray data)
{
    for(int i = 0; i < listClients_.size(); ++i)
    {
        if(listClients_[i].getSocId() == id)
        {
            listClients_[i].setLast_msg(QString(data));
        }
    }
    beginResetModel();
    endResetModel();

}

