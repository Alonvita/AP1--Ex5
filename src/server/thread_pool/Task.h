#ifndef AP1_TASK_H
#define AP1_TASK_H


#include "../view/ServerClient.h"

// Base task for tasks
// run() should be overloaded and expensive calculations done there
// showTask() is for debugging and can be deleted if not used
class Task {
public:
    virtual ~Task() {}

    virtual void run()=0;
    virtual void showTask()=0;
};

#endif //AP1_TASK_H