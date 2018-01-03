/**
 * Project:    Ex5.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * TurnsManager Class.
 *
 * The TurnsManager class is in charge of everything that is linked to the
 *  turns of the games: availability, turn validity and who's turn it is.
 */

//----------INCLUDING----------
#include "TurnsManager.h"

//----------Initialization list----------
/**
 * TurnsManager(int numPlayers, Board* gb): playerTurn((Cell) 0).
 *
 * @param numPlayers int -- number of players
 * @param gb Board* -- game board.
 */
TurnsManager::TurnsManager(int numPlayers, Board *gb) : playerTurn((Cell) 0) {
    if (numPlayers == 2)
        initializeTwoParticipants();
    evaluateAvailableMovesForThisTurn(gb);

    initializeOneParticipant(gb);
}

//----------DESTRUCTORS----------
/*
 * ~TurnsManager().
 */
TurnsManager::~TurnsManager() {
    //Remove both players
    vector<Player *> vec;
    players.swap(vec);
    vector<CellIndex> vec2;
    availableMoves.swap(vec2);
    delete this;
}

//----------GETTERS & SETTERS----------

/**
 * getAvailableMovesNum().
 *
 * @return int -- the number of available moves for this turn.
 */
int TurnsManager::getAvailableMovesNum() {
    return (int) availableMoves.size();
}

/**
 * getAvailableMoves().
 *
 * @return a vector of available moves.
 */
vector<CellIndex> TurnsManager::getAvailableMoves() {
    return this->availableMoves;
}

/**
 * getCurrentPlayerColor().
 *
 * @return Cell -- current playing player's color
 */
Cell TurnsManager::getCurrentPlayerColor() {
    return ((Cell) this->playerTurn);
}

/**
 * getAvailableMovesAsString().
 *
 * @return a string representing the available moves for this turn
 */
std::string TurnsManager::getAvailableMovesAsString() {
    // Local Variables
    std::string availableMovesStr = "The available moves for this turn are: \n";
    unsigned long size = availableMoves.size();

    for (unsigned long i = 0; i < size; ++i) {
        if (i == size - 1) {
            availableMovesStr += availableMoves[i].toString();
            availableMovesStr += "\n";
            continue;
        }

        availableMovesStr += availableMoves[i].toString() + ", ";
    }

    return availableMovesStr;
}

//----------Public Functions----------
/**
 * endTurn().
 *
 * This function will XOR the current player turn with 1 so that the turn is
 *  passed on to the next player.
 */
void TurnsManager::endTurn() {
    turnEndedMessage();
    this->playerTurn = (Cell) this->playerTurn ^ 1;
}


/**
 * evaluateAvailableMovesForThisTurn(board* gb).
 *
 * @param gb board* -- the game's board.
 */
void TurnsManager::evaluateAvailableMovesForThisTurn(Board *gb) {
    //clear last turn's availableMoves, get new moves and shrink
    availableMoves.clear();
    availableMoves =
            MovesEvaluator::evaluateAvailableMoves(gb, (Cell) (playerTurn));
}

/**
 * nextMove(int boardSize).
 *
 * @param boardSize int -- the board's size
 *
 * @return CellIndex* -- a reference to the move made as string holding a cell
 *  					 index as [row,col].
 */
CellIndex TurnsManager::nextMove() {
    //Local Variables
    CellIndex* playerMove;

    do {
        playerMove = (*PLAYER).makeAMove(availableMoves);
    } while (!isMoveLegal(*playerMove));

    return *playerMove;
}

//----------INITIALIZATION FUNCTIONS----------
/**
 * initializeTwoParticipants().
 */
void TurnsManager::initializeTwoParticipants() {
    players.push_back(new Participant(WHITE));
    players.push_back(new Participant(BLACK));
}

/**
 * initializeParticipantAndAI().
 */
void TurnsManager::initializeOneParticipant(Board *gb) {
    players.push_back(new AI(gb));
    players.push_back(new Participant(BLACK));
}

/**
 * isMoveLegal(CellIndex cI).
 *
 * @param cI CellIndex -- a reference to struct holding cell's index
 * 						   as [row,col]
 *
 * @return true if the move is legal or false otherwise.
 */
bool TurnsManager::isMoveLegal(CellIndex cI) {
    //Check { -1,-1 } for bad input
    if (cI.getRow() == -1 && cI.getCol() == -1) {
        illegalMove();
        return false;
    }

    int playerMoveRow = (cI).getRow();
    int playerMoveCol = (cI).getCol();

    for (unsigned i = 0; i < this->availableMoves.size(); ++i) {
        //Inner-Loop Variables
        int availableMoveRow = availableMoves[i].getRow();
        int availableMoveCol = availableMoves[i].getCol();

        //Check is the player's move matches any available moves
        if (playerMoveRow == availableMoveRow
            && playerMoveCol == availableMoveCol) {
            return true;
        }
    }

    cout << "This move is illegal" << endl;
    return false;
}