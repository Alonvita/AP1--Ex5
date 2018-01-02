//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX5_JOINCOMMAND_H
#define AP1_EX5_JOINCOMMAND_H

#include "../ServerCommand.h"

class JoinCommand : public ServerCommand {
public:
    //---------- INITIALIZATION ----------
    JoinCommand(IModel *model);
    ~JoinCommand() {}

    //---------- PUBLIC FUNCTIONS ----------
    CommandResult* execute(ServerClient* sender, std::vector<std::string> args);

private:
    //---------- LOCAL CLASS VARIABLES ----------
    IModel *model;
};

#endif //AP1_EX5_JOINCOMMAND_H
