/**
 * Project:    Ex5.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class IClient.
 *
 * IClient Interface will serve as an empty interface for client types recognition.
 */

#ifndef AP1_EX5_ICLIENT_H
#define AP1_EX5_ICLIENT_H

class IClient {
public:
    virtual int getSocket() = 0;
};

#endif //AP1_EX5_ICLIENT_H
