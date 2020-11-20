#include "taskqueue.h"

/**
 * 使用示例：
 *
 *
 *  SimpleTaskQueue simpleTaskQue;
        simpleTaskQue.Start();

        bool ret = false;
        int t1 = 0;
        int t2 = 0;

        simpleTaskQue.PushTask([&]()
        {
            t1 = 1;
            t2 = 2;
            ret = true;
        });
 *
 *
 */



TaskQueue::TaskQueue():m_pThread(nullptr), m_stop(false)
{

}


TaskQueue::~TaskQueue()
{
    if (m_pThread != nullptr)
    {
        StopAll();
        m_pThread->join();
        delete m_pThread;
        m_pThread = nullptr;
    }
}

bool TaskQueue::Start()
{
    m_spEvent.reset(new(std::nothrow) Event());
    m_pThread = new (std::nothrow) std::thread(&TaskQueue::ThreadCallBack, this);
    return (m_pThread != NULL) & (m_spEvent != NULL);
}

void TaskQueue::StopAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    ClearAll();
    m_stop = true;
    m_spEvent->SetEvent();
}

void TaskQueue::StopCurrent()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_currentTask != nullptr)
    {
        m_currentTask->Stop();
    }
}

void TaskQueue::ClearAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    StopCurrent();
    ClearQueue();
}

void TaskQueue::ClearQueue()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::queue<std::shared_ptr<SimpleTask> > tmp = std::queue<std::shared_ptr<SimpleTask> >();
    m_taskQue.swap(tmp);
}

void TaskQueue::PushTask(const std::shared_ptr<SimpleTask>& task)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_taskQue.push(task);
    m_spEvent->SetEvent();
}

void TaskQueue::PushTask(const std::function<void()> &task)
{
    PushTask(std::shared_ptr<SimpleTask>(new SimpleTask(task)));
}

void TaskQueue::ThreadCallBack()
{
    while (true)
    {
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            if (m_stop)
            {
                break;
            }
        }

        m_spEvent->Wait();

        // 将队列里的全部执行掉
        while (true)
        {
            // 取出队首
            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);

                if (m_taskQue.empty())
                {
                    break;
                }

                m_currentTask = m_taskQue.front();
                m_taskQue.pop();

                if (m_currentTask == nullptr)
                {
                    continue;
                }
            }

            // 执行任务
            m_currentTask->DoTask();

            // 准备销毁
            std::shared_ptr<SimpleTask> tmp = m_currentTask;

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = nullptr;
            }
        }
    }
}
