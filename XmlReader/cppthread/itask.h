#ifndef ITASK_H
#define ITASK_H


class ITask
{

public:
    virtual ~ITask(){}

    /** 执行任务
    */
    virtual void DoTask() = 0;

    /** 停止任务
    */
    virtual void Stop() = 0;
};

#endif // ITASK_H
