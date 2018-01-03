//
// Created by alonv on 12/29/2017.
//

#include "StartCommand.h"

#include "../../../../easy_logging/easylogging++.h"

/**
 * StartCommand(IModel* model).
 *
 * @param model IModel -- a game model type.
 */
StartCommand::StartCommand(IModel* model) {
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
CommandResult* StartCommand::execute(ServerClient* sender, std::vector<std::string> args) {
    // check if client is already in a game
    if(model->isInGame(sender)) {
        return new CommandResult(false, ERROR, "You are already in a game!", true);
    }

    if(args.size() != 2) {
        return new CommandResult(false, ERROR, "Usage: start [name]", true);
    }

    StartRequest* req = new StartRequest(sender, args[1]);

    try {
        model->createGame(req);
    } catch (exception& e) {
        return new CommandResult(false, ERROR, "Error starting game", true);
    }

    return new CommandResult(true, START, "Your game was created, please wait for an opponent\n", true);
}