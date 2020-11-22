#include "mythread.h"


MyThread::MyThread(QObject * parent)
{
}

MyThread::~MyThread(){}

void MyThread::run()
{
    while (m_bStart) {
        Task * task = popTask();
        if(task){
            task->DoTask();
            delete task;
            task = nullptr;
        }
        msleep(10);
    }
}

void MyThread::addTask(Task *task)
{
    m_mutex.lock();
    m_taskList.push_front(task);
    m_mutex.unlock();
}

Task *MyThread::popTask()
{
    m_mutex.lock();
    Task * task;
    if(m_taskList.size() == 0){
        task =  nullptr;
    }
    else{
        task = m_taskList.takeFirst();
    }
    m_mutex.unlock();
    return task;
}


