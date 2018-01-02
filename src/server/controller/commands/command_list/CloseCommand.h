//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_CLOSE_H
#define AP1_EX3_CLOSE_H


#include "../ServerCommand.h"
#include "../../../model/IModel.h"

class CloseCommand : public ServerCommand {
public:
    //---------- INITIALIZATION ----------
    CloseCommand(IModel *model);
    ~CloseCommand() {}

    //---------- PUBLIC FUNCTIONS ----------
    CommandResult* execute(ServerClient* sender, std::vector<std::string> args);

private:
    //---------- LOCAL CLASS VARIABLES ----------
    IModel *model;
};


#endif //AP1_EX3_CLOSE_H
