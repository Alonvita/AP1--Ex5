#ifndef AP1_THREADPOOL_H
#define AP1_THREADPOOL_H

#include "PoolWorkerThread.h"

class ThreadPool {
public:
    // Allocate a thread pool and set them to work trying to get objects
    ThreadPool(int n);

    // Wait for the threads to finish, then delete them
    ~ThreadPool();

    void addWorkerThreads(int n);

    // Add a task
    void addTask(Task *nt);

    // Asking the threads to finish, waiting for the task
    // queue to be consumed and then returning.
    void finish();

private:
    std::vector<PoolWorkerThread *> threads;
    WorkQueue workQueue;
};

#endif //AP1_THREADPOOL_H