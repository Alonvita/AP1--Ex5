//
// Created by alonv on 12/29/2017.
//

#include "CommandResult.h"

/**
 * toString().
 *
 * @return a string representation of this CommandResult.
 */
std::string CommandResult::toString() {
    std::string cmdResAsString;

    cmdResAsString = intToString((int) success);
    cmdResAsString += " ";
    cmdResAsString += intToString((int) command);
    cmdResAsString += " ";
    cmdResAsString += intToString((int) keepConnection);
    cmdResAsString += " ";
    cmdResAsString += data;

    return cmdResAsString;
}

/**
 * fromString(std::string str).
 *
 * @param str string -- a string.
 *
 * @return a referense to a new CommandResult representing this string.
 */
CommandResult* CommandResult::fromString(std::string str) {
// Local Variables
    std::vector<std::string> splitStr = split(str, ' ');
    CommandResult* msg = nullptr;
    char* endP;

    // get success
    bool success = (bool) strtol(splitStr[0].c_str(), &endP, 10);

    // get notification type
    int cmdType = (int) strtol(splitStr[3].c_str(), &endP, 10);
    Command cmdT;

    switch (cmdType) {
        case JOIN:
            cmdT = JOIN;
            break;
        case LIST:
            cmdT = LIST;
            break;
        case PLAY:
            cmdT = PLAY;
        case CLOSE:
            cmdT = CLOSE;
        case START:
            cmdT = START;
        default:
            cmdT = UNDEFINED;
            break;
    }

    // get keepConnection
    bool keepCon = (bool) strtol(splitStr[3].c_str(), &endP, 10);

    if(cmdT == UNDEFINED)
        std::runtime_error("Bad notification type: " + cmdT);

    msg = new CommandResult(success, cmdT, splitStr[0], keepCon);

    return msg;
}

/**
 * getKeepConnection().
 *
 * @return true to keep the connection, or false to close it.
 */
bool CommandResult::getKeepConnection() {
    return this->keepConnection;
}

/**
 * getCommandSuccess().
 *
 * @return true if command succeeded, or false otherwise
 */
bool CommandResult::getCommandSuccess() {
    return this->success;
}
/**
 * getType().
 *
 * @return the type of the message.
 */
Command CommandResult::getType() {
    return this->command;
}

/**
 * getData().
 *
 * @return the data held by this message.
 */
std::string CommandResult::getData() {
    return this->data;
}