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
    //LINFO << "Handling game started";
    Notification *notif =
            new Notification(rG->getBoard()->toString(), GAME_STARTED);
    std::vector<ReversiGamePlayer *> *clients = rG->getAllClients();

    unsigned long size = clients->size();

    for (unsigned long i = 0; i < size; ++i) {
        ReversiGamePlayer *player = ((ReversiGamePlayer *) (*clients)[i]);
        IClient *client1 = player->getClient();
        //LINFO << "Checking player: " << client1->getSocket() << " color: " << player->getColor();

        // notify second player that he has joined the game
        if (player->getColor() == BLACK) {
            //LINFO << "Color of " << client1->getSocket() << " is BLACK" << " - sending him \'joined_game\' notif";
            Notification *joinedGameNotif = new Notification("joined_game", GAME_STARTED);

            clientNotifier->notifyClient(client1, joinedGameNotif);

            //send board
            clientNotifier->notifyClient(client1, notif);
        }

        // notify first player that game has started
        if (player->getColor() == WHITE) {
            //LINFO << "Color of " << client1->getSocket() << " is WHITE" << " - sending him \'game started\' notif";
            Notification *gameStartedNotif =
                    new Notification("Your game has started!", GAME_STARTED);

            //LINFO << "Notifying player with his game started noification";
            // notify
            clientNotifier->notifyClient(client1, gameStartedNotif);

            //LINFO << "Notifying player with board";
            // send board
            clientNotifier->notifyClient(client1, notif);

            //LINFO << "Notifying player with available moves";
            // notify with available moves
            notifyAvailableMoves(rG, ((ServerClient *) client1));
        }
        //LINFO << "Loop ended for " << client1->getSocket() << ", " << player->getColor();
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
            //LINFO << "The game " << rG->getName() << " has ended: ";
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
    LINFO << "Handling move made by: " << player->getSocket();
    // Local Variables
    MoveUpdate *update = new MoveUpdate(rG->getName(), cI);
    Notification *updateNotif = new Notification(update->toString(), PLAYER_MOVE);
    Notification *boardNotif =
            new Notification(rG->getBoard()->toString(), GAME_STARTED);
    std::vector<ReversiGamePlayer *> *clients = rG->getAllClients();

    for (unsigned i = 0; i < clients->size(); ++i) {
        // inner loop variables
        std::string message;
        ReversiGamePlayer *player1 = ((ReversiGamePlayer *) (*clients)[i]);
        ServerClient *client1 = (ServerClient *) player1->getClient();

        if (client1->getSocket() == ((ServerClient *) player)->getSocket()) {
            // send the board as a message
            clientNotifier->notifyClient(client1, updateNotif);
            clientNotifier->notifyClient(client1, boardNotif);
            continue;
        }

        //LINFO << "Notifying: " << client1->getSocket() << " with board update -> this player did NOT make the move";

        // notify the other client with the move made
        clientNotifier->notifyClient(client1, updateNotif);

        // notify with board update
        clientNotifier->notifyClient(client1, boardNotif);

        // notify the other client with available moves
        notifyAvailableMoves(rG, client1);
    }
}

/**
 * notifyAvailableMoves(ReversiGame *rG, IClient *player).
 * @param rG ReversiGame* -- a referense to the game the player is playing on
 * @param player IClient -- a client to notify.
 */
void Controller::notifyAvailableMoves(ReversiGame *rG, ServerClient *client) {
    std::vector<CellIndex> availableMoves = rG->getAvailableMoves();
    std::string availableMovesStr = "Your available moves for this turn are:\n";
    unsigned long size = availableMoves.size();

    for (unsigned long i = 0; i < size; ++i) {
        if (i == size - 1) {
            availableMovesStr += availableMoves[i].toString();
            availableMovesStr += "\n";
            continue;
        }

        availableMovesStr += availableMoves[i].toString() + ", ";
    }

    //LINFO << "AvailableMovesStr";
    Notification *notif = new Notification(availableMovesStr, PLAYER_MOVE);
    clientNotifier->notifyClient(client, notif);

    //player will be notified with "available_moves" from command
}

/**
 * handleIllegalMove(ReversiGame *rG, IClient *player).
 *
 * @param rG ReversiGame* -- a reference to the game this illegal move was
 *                              made on.
 * @param player IClient -- the player that made this move.
 */
void Controller::handleIllegalMove(ReversiGame *rG, IClient *player) {
    //LINFO << "Handling illegal move";
    // Local Variables
    Notification *notif = new Notification("illegal_move", PLAYER_MOVE);

    clientNotifier->notifyClient(((ServerClient *) player), notif);
}

/**
 * handleException()
 */
void Controller::handleException(std::string exception, IClient *player) {
    //LINFO << "Handling Exception";
    // Local Variables
    Notification *notif = new Notification(exception, PLAYER_MOVE);


    clientNotifier->notifyClient(((ServerClient *) player), notif);
}