/*
 * Project:    Ex3.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * AI Class.
 *
 * An AI is a computer that will serve as a second player. It will
 *  evaluate it's best moves to make and send them as a string to
 *  the TurnsManager.
 *
 */

//----------INCLUDING---------
#include "AI.h"

//----------INITIALIZER-LIST----------

/**
 * AI(Cell c, Board* gb) Constructor.
 *
 * @param gb Board -- the game's board
 */
AI::AI(Board *gameBoard) : Player(WHITE, gameBoard) {}

//---------- DESTRUCTOR ----------

/**
 * ~AI();
 */
AI::~AI() {
    delete this->gameBoard;
    delete this;
}

//----------PUBLIC FUNCTIONS----------
/**
 * makeMove().
 *
 * @return CellIndex -- a CellIndex representing AI's move.
 */
CellIndex *AI::makeAMove(vector<CellIndex> availableMoves) const {
    //Local Variables
    CellIndex bestMove = {-1, -1};

    //Inner-Loop Local Variables
    int minPotential = INT_MAX;

    //This loop is for simulating AI moves
    for (unsigned i = 0; i < availableMoves.size(); ++i) {
        //Get a new Simulation Board
        Board *simulationBoard = gameBoard->getBoardAsObject(); //Copy board
        //Simulate move
        simulationBoard->moveMade(availableMoves[i], AI_COLOR);

        //for simulated move, evaluate moves for Player's turn
        vector<CellIndex> simAvailableMoves =
                MovesEvaluator::
                evaluateAvailableMoves(simulationBoard, PLAYER_COLOR);

        //find potential for ALL Player's moves
        int potential = calculatePotential(simulationBoard, simAvailableMoves);

        //Look for the minimal player potential for best AI move
        if (potential < minPotential) {
            //set new minPotential and bestMove
            minPotential = potential;
            bestMove = (availableMoves[i]);
        }

        delete simulationBoard;
    }

    printAIMove(bestMove);

    vector<CellIndex> vec;
    availableMoves.swap(vec);

    return new CellIndex(bestMove.getRow(), bestMove.getCol());
}

//----------PRIVATE FUNCTIONS----------
/**
 * calculatePotential(Board* gb, vector<CellIndex> vec) const.
 *
 * @param gb Board* -- a game board.
 * @vec vector<CellIndex> -- vector of moves
 *
 * @return the potential for the WHOLE vector moves
 */
int AI::calculatePotential(Board *gb, vector<CellIndex> vec) const {
    //Local Variables
    int potential = 0;

    //This loop is for evaluating player's potential for each AI move
    for (unsigned j = 0; j < vec.size(); ++j) {
        //simulate move
        gb->moveMade(vec[j], PLAYER_COLOR);
        vector<CellIndex> cellsInUse = gb->getCellsInUse();

        //Count the potential
        for (unsigned k = 0; k < cellsInUse.size(); ++k) {
            //Inner-Loop Local Variables
            Cell boardCell =
                    gb->getBoardCell(cellsInUse[k].getRow(),
                                     cellsInUse[k].getCol());

            if (boardCell == PLAYER_COLOR) { ++potential; }
        }
    }

    return potential;
}