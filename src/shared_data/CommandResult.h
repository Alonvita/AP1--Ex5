//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_COMMANDRESULT_H
#define AP1_EX3_COMMANDRESULT_H

#include <string>

#include "utility/StringSerializing.h"

typedef enum command {
    UNDEFINED = -1,
    LIST,
    JOIN,
    PLAY,
    CLOSE,
    START,
    ERROR
} Command;

class CommandResult {
public:
    CommandResult(bool success, Command cmd, std::string payLoad, bool keepCon) :
            success(success), command(cmd), data(payLoad), keepConnection(keepCon) {};

    // from and to string
    std::string     toString();
    CommandResult*  fromString(std::string str);

    // getters & setters
    bool getKeepConnection();
    bool getCommandSuccess();
    Command     getType();
    std::string getData();

private:
    bool        keepConnection;
    bool        success;
    Command     command;
    std::string data;

};

#endif //AP1_EX3_COMMANDRESULT_H
