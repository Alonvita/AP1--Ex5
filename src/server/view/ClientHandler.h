//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_CLIENTHANDLER_H
#define AP1_EX3_CLIENTHANDLER_H


#include "IClientHandler.h"
#include "IClientNotifier.h"
#include "../thread_pool/Task.h"
#include "../controller/Controller.h"
#include "../../shared_data/Notification.h"
#include "../thread_pool/ThreadPool.h"
#include "../thread_pool/tasks/ClientTask.h"

class ClientHandler : public IClientHandler, public IClientNotifier {
public:
    ClientHandler();
    ~ClientHandler();

    // client handling
    void handleClient(IClient* client);
    void notifyClient(IClient* client, Notification* notification);
    void createClientTask(IClient* client);

    // getters and setters
    ClientTask* getClientTask();

private:
    IClient* client;
    ClientTask* task;
    Controller* controller;
};


#endif //AP1_EX3_CLIENTHANDLER_H