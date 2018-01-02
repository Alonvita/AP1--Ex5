#ifndef AP1_WORKQUEUE_H
#define AP1_WORKQUEUE_H


#include <pthread.h>
#include <queue>
#include "Task.h"

// Wrapper around std::queue with some mutex protection
class WorkQueue
{
public:
    WorkQueue();
    ~WorkQueue();
    // Retrieves the next task from the queue
    Task *nextTask();
    // Add a task
    void addTask(Task *nt);

private:
    std::queue<Task*> tasks;
    pthread_mutex_t qmtx;
    pthread_cond_t wcond;
};


#endif //AP1_WORKQUEUE_H