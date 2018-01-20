//
// Created by alon_vita on 1/3/18.
//

#ifndef AP1_EX3_SERVERTASK_H
#define AP1_EX3_SERVERTASK_H


#include "../Task.h"
#include "../ThreadPool.h"
#include "ClientTask.h"

class ServerTask : public Task {
public:
    ServerTask(ThreadPool *threadPool, int serverSocket, int workingThreads);
    ~ServerTask();

    // task
    void run();
    void stop();
    void showTask() {}

private:
    int serverSocket;
    int workingThreads;
    ThreadPool *threadPool;
    std::vector<ClientTask*> clientTasks;

    //---------- PRIVATE FUNCTIONS ----------
    int     clientConnected(int serverSocket);
    void    writeClientOptions(int clientSocket);

};


#endif //AP1_EX3_SERVERTASK_H
