//
// Created by alonv on 12/29/2017.
//


#include "Notification.h"

/**
 * toString().
 *
 * @return a string representation of this notification.
 */
std::string Notification::toString() {
    std::string notificationAsString;

    notificationAsString = intToString(notificationType);
    notificationAsString += " ";
    notificationAsString += data;

    return notificationAsString;
}

/**
 * fromString(std::string str).
 *
 * @param str std::string -- a string.
 * @return a reference to a new Notification representing the given string.
 */
Notification* Notification::fromString(std::string str) {
    // Local Variables
    std::vector<std::string> splitStr = split(str, ' ');
    Notification* notif = nullptr;
    char* endP;

    // get notification type
    int notifType = (int) strtol(splitStr[1].c_str(), &endP, 10);
    NotificationType nT;

    switch (notifType) {
        case GAME_STARTED:
            nT = GAME_STARTED;
            break;
        case GAME_OVER:
            nT = GAME_OVER;
            break;
        case PLAYER_MOVE:
            nT = PLAYER_MOVE;
            break;
        default:
            nT = BAD_COMMAND;
            break;
    }

    if(nT == BAD_COMMAND)
        std::runtime_error("Bad notification type: " + notifType);

    notif = new Notification(splitStr[0], nT);

    return notif;
}

/**
 * getData().
 *
 * @return the notification's data.
 */
std::string Notification::getData() {
    return this->data;
}

/**
 * getNotifType().
 *
 * @return the motification type.
 */
NotificationType Notification::getNotifType() {
    return this->notificationType;
}