#include "task.h"

Task::Task(const std::function<void()> &func):mCallback(func)
{

}


void Task::DoTask(){
    mCallback.operator()();
}
