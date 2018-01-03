/**
 * Project:    Ex5.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class Controller.
 *
 * The controller will parse Client's messages accordingly.
 */


#include "Controller.h"
#include "commands/command_list/PlayCommand.h"
#include "commands/command_list/StartCommand.h"
#include "commands/command_list/CloseCommand.h"
#include "commands/command_list/JoinCommand.h"

#include "../../easy_logging/easylogging++.h"

//---------- INITIALIZATION ----------
/**
 * Controller(vector<ClientSocket> clients): clients(clients).
 *
 * Creates a controller with given ClientSocket vector for messaging clients.
 *  Also initializes a TurnsManager and a Board.
 */
Controller::Controller(IClientNotifier *clientNotifier) {
    this->model = new Model(this);
    this->clientNotifier = clientNotifier;

    commandSet.push_back(MyPair("join", new JoinCommand(this->model)));
    commandSet.push_back(MyPair("close", new CloseCommand(this->model)));
    commandSet.push_back(MyPair("start", new StartCommand(this->model)));
    commandSet.push_back(MyPair("list", new ListCommand(this->model)));
    commandSet.push_back(MyPair("play", new PlayCommand(this->model)));
    //LINFO << "commandSet addresses: " << "\n" << "join: " << commandSet[0].second << "\n" << "close: " << commandSet[1].second << "\n" << "start: " << commandSet[2].second << "\n" << "list: " << commandSet[3].second << "\n" << "play: " << commandSet[4].second;
}

//---------- PUBLIC FUNCTIONS ----------

/**
 * executeCommand(string command, IClient sender).
 *
 * @param command string -- a command as a string
 * @param sender IClient -- a client type.
 *
 * @return the result of the command.
 */
CommandResult *Controller::executeCommand(string command, IClient *sender) {
    // Local Variables
    std::vector<std::string> args = split(command, ' ');
    std::string commandName;

    if (args.size() > 0) {
        commandName = args[0];
    } else {
        commandName = "unknown_command";
    }

    // find command pointer in map
    ICommand *cmd = nullptr;

    std::string commandNameFromSet;
    unsigned long size = commandSet.size();

    for (unsigned long i = 0; i < size; ++i) {
        commandNameFromSet = commandSet[i].first;
        if (strcmp(commandNameFromSet.c_str(), commandName.c_str()) == 0) {
            cmd = commandSet[i].second;
            //LINFO << "A command was found: " << commandSet[i].second;
            break;
        }
    }


    // command was not found
    if (cmd == nullptr) {
        //LDEBUG << "Undefined command: " << command;
        return new CommandResult(false, UNDEFINED, "Unknown Command", true);
    }

    //LINFO << "Trying to execute command: " << cmd;
    CommandResult *result = ((ServerCommand *) cmd)->execute((ServerClient *) sender, args);
    //LINFO << commandName << " for: " << sender->getSocket() << " executed succesfuly";

    return result;
}


/**
 * handleGameStarted(Reversi game).
 *
 * @param rG ReversiGame* -- a reference to reversi game
 */
void Controller::handleGameStarted(ReversiGame *rG) {
    // Local Vriables
    std::vector<ReversiGamePlayer *> *clients = rG->getAllClients();
    unsigned long size = clients->size();

    for (unsigned long i = 0; i < size; ++i) {
        ReversiGamePlayer *player = ((ReversiGamePlayer *) (*clients)[i]);
        IClient *client1 = player->getClient();

        // notify second player that he has joined the game
        if (player->getColor() == BLACK) {
            std::string msgBlackPlayer = "joined game\n";
            msgBlackPlayer += rG->getBoard()->toString();

            clientNotifier->notifyClient(player->getClient(), new Notification(msgBlackPlayer, GAME_STARTED));
        }

        // notify first player that game has started
        if (player->getColor() == WHITE) {
            std::string msgWhitePlayer = "Some one has entered your game!\n";
            msgWhitePlayer += rG->getBoard()->toString() + "\n";
            msgWhitePlayer += rG->getAvailableMovesAsString();

            clientNotifier->notifyClient(client1, new Notification(msgWhitePlayer, GAME_STARTED));
        }
    }
}

/**
 * handleGameOver(ReversiGame* rG, GameOverEventArgs args).
 *
 * @param rG ReversiGame* -- a reference to reversi game
 * @param args GameOverEventArgs -- the game over event arguments.
 */
void Controller::handleGameOver(ReversiGame *rG, GameOverEventArgs *args) {
    LINFO << "Handling game over";
    // Local Variables
    std::vector<ReversiGamePlayer *> *clients = rG->getAllClients();
    ServerClient *winner = (ServerClient *) args->getWinner()->getClient();

    for (unsigned i = 0; i < clients->size(); ++i) {
        // inner loop variables
        std::string message;
        ReversiGamePlayer *player = ((ReversiGamePlayer *) (*clients)[i]);
        ServerClient *client1 = (ServerClient *) player->getClient();

        if (winner == nullptr) {
            message = "game_closed";
        } else {
            message =
                    client1->getSocket() ==
                    winner->getSocket() ? "You Win!\n" : "You Lost!\n";
        }

        // create game over details
        Notification *notif = new Notification(message, GAME_OVER);
        clientNotifier->notifyClient(client1, notif);
    }
}

/**
 * handlePlayerMoved(ReversiGame *rG, IClient *player, CellIndex cI).
 * @param rG ReversiGame* -- the reversi game that the move was made on.
 * @param player IClient -- a client type.
 * @param cI CellIndex -- the move made
 */
void Controller::handlePlayerMoved(ReversiGame *rG, IClient *player, CellIndex cI) {
    // Local Variables
    MoveUpdate *update = new MoveUpdate(rG->getName(), cI);
    std::vector<ReversiGamePlayer *> *clients = rG->getAllClients();

    // make the update notification
    std::string updateString = update->toString() + "\n" + rG->getBoard()->toString();

    // notify clients
    for (unsigned i = 0; i < clients->size(); ++i) {
        // inner loop variables
        std::string message;
        ReversiGamePlayer *player1 = ((ReversiGamePlayer *) (*clients)[i]);
        ServerClient *client1 = (ServerClient *) player1->getClient();

        if (client1->getSocket() == ((ServerClient *) player)->getSocket()) {
            // notify player
            clientNotifier->notifyClient(client1, new Notification(updateString, PLAYER_MOVE));
            continue;
        }

        // add available moves to board message
        std::string updateStringWithAMoves = updateString + "\n";
        updateStringWithAMoves += rG->getAvailableMovesAsString();

        // notify opponent
        clientNotifier->notifyClient(client1, new Notification(updateStringWithAMoves, PLAYER_MOVE));
    }
}