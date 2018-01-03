//
// Created by alon_vita on 1/3/18.
//

#ifndef AP1_EX3_SERVERTASK_H
#define AP1_EX3_SERVERTASK_H


#include "../Task.h"
#include "../ThreadPool.h"

class ServerTask : public Task {
public:
    ServerTask(ThreadPool *threadPool, int serverSocket);
    ~ServerTask() {};

    // task
    void run();
    void showTask() {}

private:
    int serverSocket;
    ThreadPool *threadPool;

    //---------- PRIVATE FUNCTIONS ----------
    int     clientConnected(int serverSocket);
    void    writeClientOptions(int clientSocket);

};


#endif //AP1_EX3_SERVERTASK_H
