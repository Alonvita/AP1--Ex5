/*
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class Server.
 *
 * This class will handle everything on the server side.
 */


#ifndef AP1_EX3_SERVER_H
#define AP1_EX3_SERVER_H

//----------INCLUDING----------
#include <string>
#include <unistd.h>
#include <iostream>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../../game/game_flow/Reversi.h"
#include "../../server/thread_pool/ThreadPool.h"
#include "../view/ClientHandler.h"
#include "../thread_pool/tasks/ServerTask.h"


//----------DEFINITIONS----------
#define MAX_CONNECTED_CLIENTS 10

using namespace std;

class Server {
public:
    //----------PUBLIC FUNCTIONS----------
    Server     (int port);
    void        start();
    void        stop();
    virtual     ~Server();

protected:
    //----------PUBLIC FUNCTIONS----------
    void        initSocket();

private:
    // Local Class Variables
    int         port;
    int         serverSocket;
    int         workingThreads;
    ThreadPool* threadPool;
    ServerTask* sTask;
};


#endif //AP1_EX3_SERVER_H