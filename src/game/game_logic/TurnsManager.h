/*
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * TurnsManager Class.
 *
 * The TurnsManager class is in charge of everything that is linked to the
 *  turns of the games: availability, turn validity and who's turn it is.
 */

#ifndef TURNS_MANAGER_H_
#define TURNS_MANAGER_H_

//----------INCLUDING----------
#include <vector>
#include <iostream>
#include <string>
#include "MovesEvaluator.h"
#include "../board/Board.h"
#include "../board/Cell.h"
#include "../players/AI.h"
#include "../players/Participant.h"
#include "../utilities/GameUtilities.h"
#include "../../display/Display.h"

//----------DEFINITIONS----------
#define PLAYER this->players.at(playerTurn)

using namespace std;


class TurnsManager: MovesEvaluator {
public:
    //----------PUBLIC FUNCTIONS----------
    // Initialize
    TurnsManager();
    TurnsManager(int numPlayers, Board* gb);

    // Destruct
    ~TurnsManager();

    // Getters & Setters
    int	                getAvailableMovesNum();
    Cell				getCurrentPlayerColor();
    vector<CellIndex>   getAvailableMoves();
    std::string         getAvailableMovesAsString();

    // Utility
    void 				endTurn();
    CellIndex 			nextMove();
    void 				evaluateAvailableMovesForThisTurn(Board *gb);
    bool                isMoveLegal(CellIndex cI);

private:
    //----------VARIABLES----------
    bool 				    playerTurn;
    vector<Player*> 		players;
    vector<CellIndex>	    availableMoves;

    //----------PRIVATE FUNCTIONS----------
    // Initialization
    void	 			initializeTwoParticipants();
    void                initializeOneParticipant(Board* gb);
};

#endif /* TURNS_MANAGER_H_ */
