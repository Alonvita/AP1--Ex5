//
// Created by alonv on 12/27/2017.
//

#include "JoinCommand.h"
#include "../../../../easy_logging/easylogging++.h"

/**
 * JoinCommand(IModel* model).
 *
 * @param model IModel -- a game model type.
 */
JoinCommand::JoinCommand(IModel* model) {
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
CommandResult* JoinCommand::execute(ServerClient* sender, std::vector<std::string> args) {
    if(args.size() != 2)
        return  new CommandResult(false, ERROR, "Usage: join + [name]", true);
    //LINFO << "Executing JoinCommand for: " << sender->getSocket();

    if(model->isInGame(sender))
        return  new CommandResult(false, ERROR, "You are already inside a game...", true);

    if(!(model->gameExists(args[1])))
        return  new CommandResult(false, ERROR, "A game is not available under this name: " + args[1] +
                                                "\nmaybe it was started without you...\n", true);

    LINFO << "Creating a JoinRequest for: " << args[1];
    JoinRequest* req = new JoinRequest(sender, args[1]);

    try {
        LINFO << "Joining game through model";
        model->joinGame(req);
    } catch (exception& e) {
        LINFO << "Error while joining game through model";
        return new CommandResult(false, ERROR, "Error joining game\n", true);
    }

    return new CommandResult(true, JOIN, "joined_game", true);
}