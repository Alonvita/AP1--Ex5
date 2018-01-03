/*
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * MovesEvaluator Class.
 *
 * This class will evaluate available moves for given board.
 *
 */

//----------INCLUDING----------
#include "MovesEvaluator.h"

//----------PUBLIC FUNCTIONS----------

vector<CellIndex> MovesEvaluator:: evaluateAvailableMoves(Board* gb, Cell playerColor) const {
    //Local Variables
    vector<CellIndex> cellsInUse = gb->getCellsInUse();
    vector<CellIndex> availableMoves;

    //Itter over cellsInUse
    for(unsigned i =0 ; i < cellsInUse.size(); ++i) {
        //Inner Loop Variables
        CellIndex cell = cellsInUse[i];
        Cell currentCell =
                gb->getBoardCell(cell.getRow(),
                                 cell.getCol());

        //Check if cell's value is OPPOSITE to the playing player's value
        if((currentCell == WHITE && playerColor == BLACK)
           || (currentCell == BLACK && playerColor == WHITE)) {
            //get cell's empty neighbors
            vector<CellIndex> emptyNeighbors = gb->getEmptyNeighbors(cell);

            //For each neighbor -> check that it has potential
            for(unsigned j = 0; j < emptyNeighbors.size(); ++j) {

                //create potential vector
                vector<CellIndex> cellPotential =
                        gb->getCellPotentialAsVector(
                                emptyNeighbors[j], playerColor);

                //Cell has potential and therefore an available move!
                if(!cellPotential.empty()) {
                    //Reserve place for the vector
                    availableMoves.push_back(emptyNeighbors[j]);
                }
            }
        }
    }

    //Clear Duplicates
    clearDuplicatesValues(&availableMoves);

    return availableMoves;
}