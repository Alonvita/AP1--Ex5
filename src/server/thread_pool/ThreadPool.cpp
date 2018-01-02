#include "ThreadPool.h"

// Allocate a thread pool and set them to work trying to get objects
ThreadPool::ThreadPool(int n) {
    addWorkerThreads(n);
}

void ThreadPool::addWorkerThreads(int n) {
    if (n < 0)
        return;

    for (int i = 0; i < n; ++i) {
        threads.push_back(new PoolWorkerThread(workQueue));
        threads.back()->start();
    }
}

// Wait for the threads to finish, then delete them
ThreadPool::~ThreadPool() {
    finish();
}

// Add a task
void ThreadPool::addTask(Task *nt) {
    workQueue.addTask(nt);
}

// Asking the threads to finish, waiting for the task
// queue to be consumed and then returning.
void ThreadPool::finish() {
    for (size_t i = 0, e = threads.size(); i < e; ++i)
        workQueue.addTask(NULL);
    for (size_t i = 0, e = threads.size(); i < e; ++i) {
        threads[i]->join();
        delete threads[i];
    }
    threads.clear();
}