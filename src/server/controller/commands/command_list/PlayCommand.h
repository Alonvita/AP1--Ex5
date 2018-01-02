//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_PLAYCOMMAND_H
#define AP1_EX3_PLAYCOMMAND_H


#include <string>
#include "../ServerCommand.h"

class PlayCommand : public ServerCommand {
public:
    //---------- INITIALIZATION ----------
    PlayCommand(IModel *model);
    ~PlayCommand() {}

    //---------- PUBLIC FUNCTIONS ----------
    CommandResult* execute(ServerClient* sender, std::vector<std::string> args);

private:
    //---------- LOCAL CLASS VARIABLES ----------
    IModel *model;
};


#endif //AP1_EX3_PLAYCOMMAND_H
