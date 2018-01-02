//
// Created by alonv on 12/30/2017.
//

#ifndef AP1_EX3_CLIENT_H
#define AP1_EX3_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include "../game/board/Cell.h"

#define MAX_MESSAGE_SIZE 255

class Client {
public:
    Client(std::string serverIP, int serverPort);

    void        play();
    void        connected();
    void        writeCommandToServer();
    bool        readUntil(std::string messageType);
    bool        writeAndReadUntil(std::string messageType);
    void        connectToServer();
    void        getClientWelcomeMessage();

private:
    Cell color;
    bool myTurn;

    int                 clientSocket;
    std::string         serverIP;
    int                 serverPort;
    struct sockaddr_in  connectionDetails;
};

#endif //AP1_EX3_CLIENT_H
