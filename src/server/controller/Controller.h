/**
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class Controller.
 *
 * The controller will parse Client's messages accordingly.
 */

#ifndef AP1_EX3_CONTROLLER_H
#define AP1_EX3_CONTROLLER_H

//----------INCLUDING----------
#include <map>
#include "commands/ServerCommand.h"
#include "../view/IClientNotifier.h"
#include "commands/command_list/PlayCommand.h"
#include "commands/command_list/StartCommand.h"
#include "commands/command_list/CloseCommand.h"
#include "commands/command_list/JoinCommand.h"
#include "commands/command_list/ListCommand.h"
#include "../../shared_data/MoveUpdate.h"
#include "../model/Model.h"

typedef std::pair<std::string, ServerCommand*> MyPair;
typedef std::vector<std::pair<std::string, ServerCommand*>> MyVector;


class Controller : public IGameEventHandler {
public:
    //----------PUBLIC FUNCTIONS----------
    // Initialize
    Controller(IClientNotifier* clientNotifier);

    // Destruct
    ~Controller() {}

    // client handling
    CommandResult* executeCommand(std::string command, IClient* sender);

    // Interface Mandatory Functions
    void handleGameStarted(ReversiGame* rG);
    void handleException(std::string str, IClient *player);
    void handleIllegalMove(ReversiGame *rG, IClient *player);
    void handleGameOver(ReversiGame* rG, GameOverEventArgs* args);
    void handlePlayerMoved(ReversiGame* rG, IClient* player, CellIndex cI);
    void notifyAvailableMoves(ReversiGame *rG, ServerClient *player);

private:
    // Local Class Variables
    IModel*             model;
    IClient*            client;
    MyVector            commandSet;
    IClientNotifier*    clientNotifier;

    //----------PRIVATE FUNCTIONS----------
};


#endif //AP1_EX3_CONTROLLER_H