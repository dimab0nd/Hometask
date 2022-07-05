#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QWidget>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(int n);
    virtual ~Worker(){}

public slots:
    void doHeavyCaclulations();

signals:
    void progress(int);
private:
    bool isPrime(int n);
    int number;
    QList<int> answers;
};


#endif // WORKER_H
