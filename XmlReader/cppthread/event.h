#ifndef EVENT_H
#define EVENT_H
#include <stdlib.h>
#include <mutex>
#include <pthread_unistd.h>
#include <condition_variable>

using namespace std;

class Event
{
public:
    /** 等待一个信号
    */
    void Wait()
    {
        std::unique_lock<std::mutex> lck(m_mutex);

        if (!m_hasSignal)
        {
            // 不会死锁，考虑：
            // 1、m_mutex.unlock();
            // 2、wait()
            // 3、m_mutex.lock();
            // wait(lck) 相当于将1、2两步放到一个cpu周期内
            m_con.wait(lck);
        }

        m_hasSignal = false;
    }

    /** 设置一个信号
    */
    void SetEvent()
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_hasSignal = true;
        m_con.notify_all();
    }

private:
    /** 互斥量
    */
    std::mutex m_mutex;

    /** condition_variable
    */
    std::condition_variable m_con;

    /** 是否有信号，只是记录是否有信号，但是不记录信号次数
    @note 主要是为了先调用SetEvent()，然后调用wait的情况。考虑在Wait()前加上::Sleep(1000);
    */
    bool m_hasSignal = false;
};

#endif // EVENT_H
