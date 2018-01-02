/**
 * Project:    Ex5.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class ServerCommand.
 *
 * ServerCommand Interface.
 */

#ifndef AP1_EX5_SERVERCOMMAND_H
#define AP1_EX5_SERVERCOMMAND_H

#include "ICommand.h"
#include "../../view/ServerClient.h"
#include "../../model/IModel.h"

class ServerCommand : public ICommand {
public:
    ~ServerCommand() {}

    //---------- PUBLIC FUNCTIONS ----------
    virtual CommandResult* execute(ServerClient* client, std::vector<std::string> args) = 0;
};

#endif //AP1_EX5_SERVERCOMMAND_H
