//
// Created by alonv on 12/29/2017.
//

#include "ListCommand.h"
#include "../../../../easy_logging/easylogging++.h"

/**
 * ListCommand(IModel* model).
 *
 * @param model IModel -- a game model type.
 */
ListCommand::ListCommand(IModel* model) {
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
CommandResult* ListCommand::execute(
        ServerClient* sender, std::vector<std::string> args) {
    if(args.size() != 1)
        return  new CommandResult(false, ERROR, "Usage: list", true);
    //LINFO << "Executing ListCommand for: " << sender->getSocket();

    if(model->isInGame(sender))
        return  new CommandResult(false, ERROR, "You are in a game!", true);

    std::vector<std::string> gamesList = model->listGames();
    std::string commandsAsString;

    for(int i = 0; (unsigned) i < gamesList.size(); ++i) {
        commandsAsString += gamesList[i];
        commandsAsString += "\n";
    }

    return new CommandResult(true, LIST, commandsAsString, true);
}