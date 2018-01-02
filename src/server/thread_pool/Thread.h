#ifndef AP1_THREAD_H
#define AP1_THREAD_H


#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

class Thread
{
public:
    Thread();
    virtual ~Thread();

    void start();

    void join();

protected:
    virtual void run() = 0;

private:
    static void* threadProc(void* param);

private:
    enum EState
    {
        EState_None,
        EState_Started,
        EState_Joined
    };

    EState state;
    bool joined;
    pthread_t handle;
};


#endif //AP1_THREAD_H