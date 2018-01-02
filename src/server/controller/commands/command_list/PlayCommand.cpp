//
// Created by alonv on 12/29/2017.
//

#include "PlayCommand.h"
#include "../../../../easy_logging/easylogging++.h"


/**
 * PlayCommand(IModel* model).
 *
 * @param model IModel -- a game model type.
 */
PlayCommand::PlayCommand(IModel *model) {
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
CommandResult *PlayCommand::execute(ServerClient *sender, std::vector<std::string> args) {
    if (args.size() != 2) {
        //LERROR << "bad number of arguments to Play";
        return new CommandResult(false, ERROR, "Usage: Play row,col", true);
    }

    if (!(model->isInGame(sender))) {
        return new CommandResult(false, ERROR, "You are not in a game!", true);
    }

    //LINFO << "Executing PlayCommand: " << args [1];

    LINFO << "creating CellIndex from the given string";
    CellIndex cI;
    cI.fromString(args[1]);

    //LINFO << "CellIndex created: " << moveToString;

    if (cI.getRow() == -1 || cI.getCol() == -1) {
        //LINFO << "CellIndex (-1,-1) -> return a bad move";
        return new CommandResult(false, ERROR, "Bad move: " + args[1] + "\n", true);
    }

    //LINFO << "Creating a new PlayRequest for move: " << moveToString;
    PlayRequest *req = new PlayRequest(sender, cI);
    //LINFO << "PlayRequest was succesfuly created for move: " << moveToString;

    try {
        //LINFO << "Playing: " << moveToString << " on model";
        model->playMove(req);
    } catch (exception &e) {
        //LINFO << "Error playing move: " << moveToString;
        return new CommandResult(false, ERROR, "Error playing move\n", true);
    }
    return new CommandResult(true, PLAY, "player_move", true);
}