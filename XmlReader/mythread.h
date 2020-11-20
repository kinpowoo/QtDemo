#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMutex>
#include "task.h"

class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread(QObject* par = nullptr);
    ~MyThread();
    void addTask(Task * task); //添加任务,在最前面添加,保证最后添加的优先级最高
    Task * popTask();
    void stop(){m_bStart = false;}
    void run();
private:
    QList<Task *> m_taskList;  //任务列表
    QMutex m_mutex;
    bool m_bStart = true;
};

#endif // MYTHREAD_H
