/**
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class IClientNotifier.
 *
 * IClientNotifier will server as an interface for objects that
 *  updateBoardWithMove clients.
 */

#include "ServerClient.h"

#ifndef AP1_EX3_ICLIENTNOTIFIER_H
#define AP1_EX3_ICLIENTNOTIFIER_H

class IClientNotifier {
public:
    ~IClientNotifier() {}

    // Mandatory Functions
    virtual void notifyClient(IClient* client, Notification* notification) = 0;
};

#endif //AP1_EX3_ICLIENTNOTIFIER_H