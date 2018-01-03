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
JoinCommand::JoinCommand(IModel *model) {
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
CommandResult *JoinCommand::execute(ServerClient *sender, std::vector<std::string> args) {
    if (args.size() != 2)
        return new CommandResult(false, ERROR, "Usage: join + [name]\n", true);

    if (model->isInGame(sender))
        return new CommandResult(false, ERROR, "You are already inside a game...\n", true);

    if (!(model->gameExists(args[1])))
        return new CommandResult(false, ERROR, "A game is not available under this name: " + args[1] +
                                               "\nmaybe it was started without you...\n", true);

    JoinRequest *req = new JoinRequest(sender, args[1]);

    try {
        model->joinGame(req);
    } catch (std::string &e) {
        return new CommandResult(false, ERROR, e, true);
    }

    return new CommandResult(true, JOIN, "joined_game\n", true);
}