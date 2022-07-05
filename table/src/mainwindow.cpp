#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTable();
}

void MainWindow::initTable()
{   QStringList headers;
    headers<<"number"<<"progress";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setShowGrid(true);

    // Настройка выделения
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    // Заголовки колонок
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    for(int i = 0; i < N; i++){
//        int k = std::rand()%INT_MAX;
        int k = std::rand()%MAX_NUMBER;

        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(QString::number(k)));
        QProgressBar *pgbar = new QProgressBar();
        pgbar->setMinimum(0);
        pgbar->setMaximum(k-1);

        QThread* thread = new QThread();
        Worker* worker = new Worker(k);
        worker->moveToThread(thread);

        connect(thread, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(thread, SIGNAL(started()), worker, SLOT(doHeavyCaclulations()));
        connect(worker, SIGNAL(progress(int)), pgbar, SLOT(setValue(int)));

        listThreads.push_back(thread);

        ui->tableWidget->setCellWidget(i,1,pgbar);
    }

    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    for (int i =0; i < listThreads.size(); ++i) {
        listThreads[i]->start();
    }
}
