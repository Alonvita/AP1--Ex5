//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_NOTIFICATION_H
#define AP1_EX3_NOTIFICATION_H

#include <string>
#include <stdexcept>

#include "utility/StringSerializing.h"
#include "utility/StringSerializing.h"

typedef enum Type {
    BAD_COMMAND = -1,
    GAME_STARTED,
    GAME_OVER,
    PLAYER_MOVE
} NotificationType;

class Notification {
public:
    Notification() {};
    Notification(std::string data, NotificationType type): data(data), notificationType(type) {};
    ~Notification() {}

    // to and from strings
    std::string     toString();
    Notification*   fromString(std::string str);

    // getters & setters
    std::string      getData();
    NotificationType getNotifType();

private:
    std::string data;
    NotificationType notificationType;
};


#endif //AP1_EX3_NOTIFICATION_H
