//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_LISTCOMMAND_H
#define AP1_EX3_LISTCOMMAND_H


#include "../ServerCommand.h"

class ListCommand : public ServerCommand {
public:
    //---------- INITIALIZATION ----------
    ListCommand(IModel *model);
    ~ListCommand() {}

    //---------- PUBLIC FUNCTIONS ----------
    CommandResult* execute(ServerClient* sender, std::vector<std::string> args);

private:
    //---------- LOCAL CLASS VARIABLES ----------
    IModel *model;
};


#endif //AP1_EX3_LISTCOMMAND_H
