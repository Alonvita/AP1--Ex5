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
#include "../display/Display.h"
#include "../game/board/Cell.h"
#include "../shared_data/Message.h"
#include "../shared_data/Notification.h"

#define MAX_MESSAGE_SIZE 1024

#define MESSAGE_TYPE_OFFSET 0
#define MESSAGE_DATA_OFFSET 2
#define NOTIFICATION_TYPE_OFFSET 0
#define NOTIFICATION_DATA_OFFSET 2
#define COMMAND_RESULT_SUCCESS_OFFSET 0
#define COMMAND_RESULT_COMMAND_OFFSET 2
#define COMMAND_RESULT_KEEPCOM_OFFSET 4
#define COMMAND_RESULT_DATA_OFFSET 6


class Client {
public:
    // initialization
    Client(std::string serverIP, int serverPort);

    // server communication functions
    void writeMessageToServer();
    void readMessageFromServer();

    // server connection functions
    void connected();
    void connectToServer();
    void updateConnectionStatus();

private:
    Cell color;
    bool myTurn;
    bool stayConnected;

    int                 clientSocket;
    std::string         serverIP;
    int                 serverPort;
    struct sockaddr_in  connectionDetails;
};

#endif //AP1_EX3_CLIENT_H
