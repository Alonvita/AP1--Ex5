//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_MESSAGE_H
#define AP1_EX3_MESSAGE_H

#include <string>

typedef enum mType {
    UNKNOWN_MESSAGE_TYPE = -1,
    COMMAND_RESULT,
    NOTIFICATION
} MessageType;

class Message {
public:
    Message(std::string data, MessageType mType) : data(data), messageType(mType) {};

    // from and to string
    std::string toString();
    Message*    fromString(std::string str);

    // getters & setters
    std::string getData();
    MessageType getMessageType();

private:
    std::string data;
    MessageType messageType;
};


#endif //AP1_EX3_MESSAGE_H
