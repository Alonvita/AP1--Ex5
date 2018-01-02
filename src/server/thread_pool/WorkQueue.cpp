#include "WorkQueue.h"

WorkQueue::WorkQueue() {
    pthread_mutex_init(&qmtx, 0);

    // wcond is a condition variable that's signaled
    // when new work arrives
    pthread_cond_init(&wcond, 0);
}

WorkQueue::~WorkQueue() {
    // Cleanup pthreads
    pthread_mutex_destroy(&qmtx);
    pthread_cond_destroy(&wcond);
}

// Retrieves the next task from the queue
Task *WorkQueue::nextTask() {
    // The return value
    Task *nt = 0;

    // Lock the queue mutex
    pthread_mutex_lock(&qmtx);

    while (tasks.empty()) {
        pthread_cond_wait(&wcond, &qmtx);
    }
    nt = tasks.front();
    tasks.pop();
    // Unlock the mutex and return
    pthread_mutex_unlock(&qmtx);
    return nt;
}

// Add a task
void WorkQueue::addTask(Task *nt) {
    // Lock the queue
    pthread_mutex_lock(&qmtx);
    // Add the task
    tasks.push(nt);
    // signal there's new work
    pthread_cond_signal(&wcond);
    // Unlock the mutex
    pthread_mutex_unlock(&qmtx);
}