#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <functional>

using namespace std;

class Task
{
public:
    Task(const std::function<void()> &func);
    void DoTask();

private:
    std::function<void()> mCallback;
};
#endif // TASK_H
