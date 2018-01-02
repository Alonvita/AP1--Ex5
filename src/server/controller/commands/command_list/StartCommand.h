//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_START_H
#define AP1_EX3_START_H


#include "../ServerCommand.h"

class StartCommand : public ServerCommand {
public:
    //---------- INITIALIZATION ----------
    StartCommand(IModel* model);
    ~StartCommand() {}

    //---------- PUBLIC FUNCTIONS ----------
    CommandResult *execute(ServerClient *sender, std::vector<std::string> args);

private:
    //---------- LOCAL CLASS VARIABLES ----------
    IModel *model;
};


#endif //AP1_EX3_START_H
