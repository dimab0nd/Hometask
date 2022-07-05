#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpserver.h"
#include "tablemodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slotRemoveRecord();

private slots:

    void slotCustomMenuRequested(QPoint pos);
    void on_startServerButton_clicked();

private:
    Ui::MainWindow *ui;
    TcpServer *server;
    tablemodel * model;
};
#endif // MAINWINDOW_H
