#ifndef TASKQUEUE_H
#define TASKQUEUE_H
#include "itask.h"
#include "event.h"
#include "task.h"

#include <stdlib.h>
#include <shared_mutex>
#include <thread>
#include <functional>
#include <mutex>
#include <queue>
#include <stdio.h>
#include <iostream>


using namespace std;

class SimpleTask:ITask{
   const std::function<void()> func;
public:
   SimpleTask(const std::function<void()> &f):func(f) {

   }
   ~SimpleTask() { std::cout << "  Test::~Test()\n"; }
   void DoTask(){
       func.operator()();
   }
   void Stop(){  }
};


class TaskQueue
{
public:
    /** 构造函数
    */
    TaskQueue();

    /** 析构函数
    */
    ~TaskQueue();

public:
    /** 开始循环
    @return 是否成功
    */
    bool Start();

    /** 停止所有任务
    */
    void StopAll();

    /** 停止当前的任务
    */
    void StopCurrent();

    /** 清空所有任务包括当前的，但不停止循环
    */
    void ClearAll();

    /** 清空所有任务不包括当前的，但不停止循环
    */
    void ClearQueue();

    /** 添加一个任务
    @param [in] task 任务
    */
    void PushTask(const std::shared_ptr<SimpleTask>& task);

    /** 添加一个函数任务
    @param [in] task 任务
    */
    void PushTask(const std::function<void()>& task);

public:
    /** 线程回调
    */
    virtual void ThreadCallBack();

private:
    /** 线程
    */
    std::thread* m_pThread;

    /** 互斥量
    */
    std::recursive_mutex m_mutex;

    /** 线程事件
    */
    std::shared_ptr<Event> m_spEvent;

    /** 任务队列
    */
    std::queue<std::shared_ptr<SimpleTask> > m_taskQue;

    /** 是否停止了
    */
    bool m_stop;

    /** 当前正在执行的
    */
    std::shared_ptr<SimpleTask> m_currentTask;
};

#endif // TASKQUEUE_H
