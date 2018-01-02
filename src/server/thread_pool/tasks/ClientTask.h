//
// Created by alon on 01/01/18.
//

#ifndef AP1_EX3_CLIENTTASK_H
#define AP1_EX3_CLIENTTASK_H


#include "../Task.h"
#include "../../view/ServerClient.h"
#include "../../controller/Controller.h"

class ClientTask : public Task {
public:
    ClientTask(ServerClient* client, Controller* controller) :
            client(client), controller(controller){};
    ~ClientTask();

    // task
    void run();
    void showTask() {}

private:
    ServerClient* client;
    Controller* controller;
};


#endif //AP1_EX3_CLIENTTASK_H
