//
// Created by alonv on 12/29/2017.
//

#include "CloseCommand.h"
#include "../../../../easy_logging/easylogging++.h"

/**
 * CloseCommand(IModel* model).
 *
 * @param model IModel -- a game model type.
 */
CloseCommand::CloseCommand(IModel* model) {
    this->model = model;
}

/**
 * execute(Client* sender, std::vector<std::string> args).
 *
 * @param sender Client* -- a reference to the sending client.
 * @param args std::vector<std::string> -- command arguments as vector of strings.
 *
 * @return a reference the a new CommandResult to the command given.
 */
CommandResult* CloseCommand::execute(ServerClient* sender, std::vector<std::string> args) {
    if(args.size() != 2)
        return new CommandResult(false, ERROR, "Usage: close + [name]", true);

    if(!(model->isInGame(sender)))
        return new CommandResult(false, ERROR, "You are not in a game", true);

    CloseRequest* req = new CloseRequest(sender, args[1]);

    try {
        model->closeGame(req);
    } catch (exception& e) {
        return new CommandResult(false, ERROR, "Error closing game", true);
    }

    return new CommandResult(true, CLOSE, "game_closed", true);
}