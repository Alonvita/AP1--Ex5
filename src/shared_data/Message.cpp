//
// Created by alonv on 12/29/2017.
//

#include "Message.h"
#include "utility/StringSerializing.h"

/**
 * toString().
 *
 * @return a string representation of this message.
 */
std::string Message::toString() {
    std::string msgAsString;

    msgAsString = intToString(messageType);
    msgAsString += " ";
    msgAsString += data;

    return msgAsString;
}

/**
 * fromString(std::string str).
 *
 * @param str string -- a string.
 *
 * @return a referense to a new message representing this string.
 */
Message* Message::fromString(std::string str) {
// Local Variables
    std::vector<std::string> splitStr = split(str, ' ');
    Message* msg = nullptr;
    char* endP;

    // get notification type
    int mType = (int) strtol(splitStr[1].c_str(), &endP, 10);
    MessageType mT;

    switch (mType) {
        case NOTIFICATION:
            mT = NOTIFICATION;
            break;
        case COMMAND_RESULT:
            mT = COMMAND_RESULT;
            break;
        default:
            mT = UNKNOWN_MESSAGE_TYPE;
            break;
    }

    if(mT == UNKNOWN_MESSAGE_TYPE)
        std::runtime_error("Bad notification type: " + mT);

    msg = new Message(splitStr[0], mT);

    return msg;
}

/**
 * getData().
 *
 * @return the message's data.
 */
std::string Message::getData() {
    return this->data;
}

/**
 * getNotifType().
 *
 * @return the message type.
 */
MessageType Message::getMessageType() {
    return this->messageType;
}