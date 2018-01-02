#ifndef AP1_POOLWORKERTHREAD_H
#define AP1_POOLWORKERTHREAD_H


#include "Thread.h"
#include "WorkQueue.h"

// Thanks to the reusable thread class implementing threads is
// simple and free of pthread api usage.
class PoolWorkerThread : public Thread {
public:
    PoolWorkerThread(WorkQueue &_work_queue);

protected:
    virtual void run();

private:
    WorkQueue &work_queue;
};


#endif //AP1_POOLWORKERTHREAD_H