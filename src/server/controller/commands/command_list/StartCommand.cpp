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

    //LINFO << "Reached StartCommand with sender: " << sender->getSocket();
    if(args.size() != 2) {
        //LERROR << "Args size is incorrect";
        return new CommandResult(false, ERROR, "Usage: start [name]", true);
    }

    //LINFO << "creating a new start request";
    StartRequest* req = new StartRequest(sender, args[1]);
    //LINFO << "new start request was created successfully for: " << args[1];

    try {
        //LINFO << "Creating a new game for " << args[1];
        model->createGame(req);
        //LINFO << "Creation successful: " << args[1];
    } catch (exception& e) {
        //LERROR << "Error starting game";
        return new CommandResult(false, ERROR, "Error starting game", true);
    }

    return new CommandResult(true, START, "game_started", true);
}