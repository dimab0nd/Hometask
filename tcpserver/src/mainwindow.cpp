#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new tablemodel();
    ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSortingEnabled(false);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->lineEdit->setText("1234");
    server = new TcpServer();
//    server->start();


    QObject::connect(server, SIGNAL(newconnection(Client)), model, SLOT(slotNewConnection(Client)), Qt::DirectConnection);
    QObject::connect(server, SIGNAL(newMessage(qintptr, QByteArray)), model, SLOT(slotNewMessage(qintptr, QByteArray)), Qt::DirectConnection);
    QObject::connect(server, SIGNAL(sigDisconnected(qintptr)), model, SLOT(slotDisconnected(qintptr)), Qt::DirectConnection);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotRemoveRecord()
{

    int row = ui->tableView->selectionModel()->currentIndex().row();

    if(row >= 0){
        qDebug()  << "try to disconnect row =" << row;
        qintptr id = model->getSocIdByRow(row);
        server->disconnectClientById(id);
    }
}

void MainWindow::slotCustomMenuRequested(QPoint pos)
{

    /* Объект контекстного меню */
    QMenu * menu = new QMenu(this);
    QAction * deleteAction = new QAction("Disconnect", this);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(slotRemoveRecord())); // Обработчик удаления записи
    menu->addAction(deleteAction);


    /* menu exec */
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));

}


void MainWindow::on_startServerButton_clicked()
{
    bool ok;
    quint16 port = ui->lineEdit->text().toInt(&ok);
    if(ok)
    {
        ui->startServerButton->setEnabled(false);
        server->start(port);
        QMessageBox::information(this,"","Server is started on port" + QString::number(port));

    }
    else
    {
        QMessageBox::critical(this,"Error","Port is invalid, try again");
    }
}
