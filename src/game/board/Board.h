/*
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Board Class.
 *
 * Board will hold a 2D array of CellIndexes. It will handle prints, and will
 *  update itself after moves were made.
 *
 */

#ifndef BOARD_H_
#define BOARD_H_

//----------INCLUDING----------
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

#include "Cell.h"
#include "CellIndex.h"
#include "../utilities/GameUtilities.h"
#include "../../shared_data/utility/StringSerializing.h"

using namespace std;

//----------DEFINITIONS----------
#define BOARD this->board

//----------CONSTANTS----------
int const SMALL_BOARD_SIZE 		= 6;
int const DEFAULT_BOARD_SIZE 	= 8;
int const LARGE_BOARD_SIZE 		= 10;

//----------ENUMS----------
enum BoardType { sixBySix = 1, eightByEight, tenByTen };

class Board {
public:
    // Initialize
    Board();
    Board(int boardType);

    // Destruct
    ~Board();

    //----------PUBLIC FUNCTIONS----------
    // Getters & Setters
    int 				getSpaceLeft();
    vector<CellIndex> 	getCellsInUse();
    Cell 				getBoardCell(int row, int col);
    int					getSize();
    Board*              getBoardAsObject();
    void                setCell(int row, int col, Cell val);
    vector<CellIndex> 	getEmptyNeighbors(CellIndex cI);
    vector<CellIndex>	getCellPotentialAsVector(CellIndex cI, Cell type);

    // In-game use
    void				moveMade(CellIndex cI, Cell value);
    int*                evaluateFinalScore();

    //Utility
    bool 				cellOnBoard(int row, int col);
    string 				generateCellValue(Cell c);

    // serialization
    std::string toString();
    std::string colsNumbers();
    std::string separatingLine();

private:
    //----------VARIABLES----------
    int 				size;
    Cell** 				board;
    vector<CellIndex> 	cellsInUse;

    //----------PRIVATE FUNCTIONS----------
    // Initialization
    void 				initializeBoard();
    void 				initializeStartingCellValues();
    int 				defineBoardSize(int boardType);

    // Utility
    vector<CellIndex> 	findPotentialInPath(CellIndex cI, int dRow,
                                            int dCol, Cell type);
    void 				changeCellColor(CellIndex cI);
};

#endif /* BOARD_H_ */
