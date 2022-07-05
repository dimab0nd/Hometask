#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QCheckBox>
#include <QMessageBox>
#include <QTimer>
#include <QHeaderView>
#include "client.h"
class tablemodel : public QAbstractTableModel
{
public:
    tablemodel();
    Q_OBJECT

    QVariant headerData(int section, Qt::Orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;

signals:


public slots:
    qintptr getSocIdByRow(int row);

    void slotNewConnection(Client client);
    void slotDisconnected(qintptr id);
    void slotNewMessage(qintptr id, QByteArray data);


private:
    QList<Client> listClients_;
    QStringList headers_;



};

#endif // TABLEMODEL_H
