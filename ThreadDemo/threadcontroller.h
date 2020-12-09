#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QtConcurrent>
#include <QtConcurrent/QtConcurrentDepends>
#include <QThread>
#include <QRunnable>
#include <QThreadPool>
#include <QDebug>
#include <QObject>
#include <QtConcurrent>
#include <functional>
#include <stdlib.h>

using namespace std;

class ThreadController:public QObject
{
    Q_OBJECT
public:
    ThreadController(QObject *p=0);
    ~ThreadController();


    Q_INVOKABLE void execTask(int a,int b);
    Q_INVOKABLE int execAsync(int a,int b);
signals:
    void sendResult(int result);
    void calResult(int result);
public slots:
    void recieveResult(int result);

private:
    QThreadPool *threadPool;
};


class Task: public QRunnable{
    ThreadController *c;
    int a,b;
public:
    Task(ThreadController *controll,int a,int b){
        c = controll;
        this->a = a;
        this->b = b;
    }
    void run(){
        //qDebug()<<"子线程id名:"<<QThread::currentThreadId();
        emit c->sendResult(a*b);
    }
};

#endif // THREADCONTROLLER_H
