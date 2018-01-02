/*
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class Board.
 *
 * Board will hold a 2D array of CellIndexes. It will handle prints, and will
 *  update itself after moves were made.
 */

//----------INCLUDES----------
#include "Board.h"

//----------Initializer List----------
/**
 * board() Default Constructor.
 *
 * @param boardType int -- default board size is 8x8.
 */
Board::Board() : size(defineBoardSize(eightByEight)) {
    initializeBoard();
}

//----------Initializer List----------
/**
 * board(int boardType) Constructor.
 *
 * @param boardType int -- board has 3 different types:
 * 							1. 6x6
 * 							2. 8x8 (also default)
 * 							3. 10x10
 */
Board::Board(int boardType) : size(defineBoardSize(boardType)) {
    initializeBoard();
}


//----------DESTRUCTOR----------
/**
 * ~board() Destructor.
 */
Board::~Board() {
    //Delete all pointers to Cell items from board
    for (unsigned i = 0; i < (unsigned) size; ++i) {
        delete[] this->board[i];
    }

    delete[] this->board; //Delete board
}

//---------- GETTERS & SETTERS ----------

/**
 * getSpaceLeft().
 *
 * @return int -- the number of cells left to play on
 */
int Board::getSpaceLeft() {
    return (int) (size * size - cellsInUse.size());
}

/**
 * getCellsInUse().
 *
 * @return vector<CellIndex> -- a vector with all cells in use
 */
vector<CellIndex> Board::getCellsInUse() {
    return this->cellsInUse;
}

/**
 * getBoardCell(int row, int col).
 *
 * @param row int -- row.
 * @param col int -- col
 * @return the color of this cell.
 */
Cell Board::getBoardCell(int row, int col) {
    if (0 <= row && row < size && 0 <= col && col < size) {
        return BOARD[row][col];
    }
    return OUT_OF_BOUNDS;
}

/*
 * getSize().
 *
 * @return int -- the board's size
 */
int Board::getSize() {
    return this->size;
}

//---------- PUBLIC FUNCTIONS ----------
/**
 * cellOnBoard().
 *
 * @return true if cell is on board or false otherwise.
 *
 */
bool Board::cellOnBoard(int row, int col) {
    return (0 <= row && row < this->size && 0 <= col && col < this->size);
}

/*
 * evaluateFinalScore().
 *
 * @return an array with the scores of both players [WHITE,BLACK]
 */
int *Board::evaluateFinalScore() {
    //Local Variables
    int *scoresArray = new int[2];
    scoresArray[0] = 0;
    scoresArray[1] = 0;

    for (unsigned i = 0; i < (unsigned) size; ++i) {
        for (unsigned j = 0; j < (unsigned) size; ++j) {
            if (board[i][j] == WHITE) {
                scoresArray[0]++;
            } else {
                scoresArray[1]++;
            }
        }
    }

    return scoresArray;
}

/*
 * getBoardAsObject();
 *
 * @return board* -- a new board, containing the same values as this one.
 */
Board *Board::getBoardAsObject() {
    //Local Variables
    int type = size == 6 ? 1 : size == 6 ? 2 : 3;
    Board *copiedBoard = new Board(type);

    //for all cells on board
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            copiedBoard->setCell(i, j, this->board[i][j]); //set cell
        }
    }

    return copiedBoard;
}

//Setters
/*
 * setCell(int row, int col, Cell val).
 *
 * @param row int -- row number
 * @param col int -- col number
 * @param val Cell -- the cell's status
 */
void Board::setCell(int row, int col, Cell val) {
    this->board[row][col] = val;
}

//----------IN-GAME USED FUNCTIONS-----------
/*
 * getEmptyNeighbors(CellIndex cI).
 *
 * @param cI CellIndex -- struct that holds the cell's index as [row,col]
 *
 * @return vector<CellIndex> -- a vector of all neighbor cell to a given cell
 */
vector<CellIndex> Board::getEmptyNeighbors(CellIndex cI) {
    //Local Variables
    vector<CellIndex> emptyNeighborsVector;
    int x = cI.getRow();
    int y = cI.getCol();

    //this loop runs between -1 and 1 to check neighbor rows
    for (int i = -1; i <= 1; i++) {
        //this loop runs between -1 and 1 to check neighbor cols
        for (int j = -1; j <= 1; j++) {
            //if index on board
            if (0 <= x + i && x + i < size && 0 <= y + j && y + j < size) {
                Cell cell = this->board[x + i][y + j];

                if (cell == EMPTY) { //check for empty values
                    //create cell's index array
                    CellIndex index = {x + i, y + j};

                    //empty value --> push cell's index to the list
                    emptyNeighborsVector.push_back(index);
                }
            }
        }
    }

    //return the vector
    return emptyNeighborsVector;
}

/*
 * getCellPotentialAsVector(CellIndex cI, Cell type).
 *
 * @param cI CellIndex -- struct that olds the cel's index as [row,col]
 * @param type Cell -- a given cell value
 *
 * @return vector<CellIndex> -- a list of ALL cells affected by the given move.
 */
vector<CellIndex> Board::getCellPotentialAsVector(CellIndex cI, Cell type) {
    //Local Variables
    vector<CellIndex> potentialVector;
    int dRow, dCol;

    for (dRow = -1; dRow <= 1; dRow++) {
        for (dCol = -1; dCol <= 1; dCol++) {
            //Get potential in this path
            vector<CellIndex> potentialInPath =
                    findPotentialInPath(cI, dRow, dCol, type);

            //Check that potential is not empty
            if (!potentialInPath.empty()) {
                //reserve space
                potentialVector.reserve(
                        potentialVector.size() + potentialInPath.size());
                //add potential
                potentialVector.insert(potentialVector.end(),
                                       potentialInPath.begin(),
                                       potentialInPath.end());
            }
        }
    }

    return potentialVector;
}

/*
 * moveMade(CellIndex* cI, Cell value).
 *
 * @param cI CellIndex* -- a reference to a cell structure that holds cell's
 * 						   cell's index as [row,col]
 * @paramvalue Cell -- a call's value
 *
 * @return the number of cells left to play on
 */
void Board::moveMade(CellIndex cI, Cell value) {
    //Local Variables
    int row = (cI).getRow();
    int col = (cI).getCol();
    vector<CellIndex> cellsEffected =
            this->getCellPotentialAsVector(cI, value);

    //Clear Duplicates
    clearDuplicatesValues(&cellsEffected);

    //-----Take Care of the Specific Cell-----

    //Change the cell's value
    BOARD[row][col] = value;

    //Add cell to used cells
    this->cellsInUse.push_back(cI);

    //-----Change board Accordingly-----
    for (unsigned i = 0; i < cellsEffected.size(); ++i) {
        //Change the color of each cell according to the game rules
        this->changeCellColor(cellsEffected[i]);
    }
}

//----------UTILITY----------
//----------Private Functions----------
/*
 * initializeBoard().
 */
void Board::initializeBoard() {
    //Allocate space for the board
    BOARD = new Cell *[size];
    for (int i = 0; i < size; i++) {
        BOARD[i] = new Cell[size];
        for (int j = 0; j < size; j++) {
            BOARD[i][j] = EMPTY;
        }
    }

    initializeStartingCellValues();
}

/*
 * defineBoardSize(int boardType).
 *
 * @param boardType int -- a board type used to set size.
 *
 * @return the size of the board
 */
int Board::defineBoardSize(int boardType) {
    switch (boardType) {
        case sixBySix:
            return SMALL_BOARD_SIZE;
        case tenByTen:
            return LARGE_BOARD_SIZE;
        default:
            return DEFAULT_BOARD_SIZE;
    }
}

/*
 * initializeStartingCellValues().
 */
void Board::initializeStartingCellValues() {
    //For runs from size/2 - 1 to size
    for (int i = size / 2 - 1; i <= size / 2; i++) {
        //For runs from size/2 - 1 to size
        for (int j = size / 2 - 1; j <= size / 2; j++) {
            //Inner-Loop Variables
            CellIndex cellIndex = {i, j};

            //set value as '0' or '1' as enum values for white and black
            BOARD[i][j] = Cell(abs(i - j));
            //push the cell index to used cells
            this->cellsInUse.push_back(cellIndex);
        }
    }
}

/*
 * generateCellValue().
 *
 * @param c Cell -- a cell type
 *
 * @return a string used to pring the board with cell values on it.
 */
string Board::generateCellValue(Cell c) {
    switch (c) {
        case WHITE:
            return "O";
        case BLACK:
            return "X";
        default:
            return " ";
    }
}

/*
 * findPotentialInPat(CellIndex cI, int dRow, int dCol, Cell type).
 *
 * @param cI CellIndex -- a struct that holds a cell's index as [row,col]
 * @param dRow int -- a row number
 * @param dCol int -- a column number
 * @param type Cell -- a cell type
 *
 * @return vector<string> -- a vector with all type-cells in a path.
 */
vector<CellIndex> Board::findPotentialInPath(CellIndex cI, int dRow,
                                             int dCol, Cell type) {
    //Local Variables
    vector<CellIndex> potentialInPath;
    int row = cI.getRow() + dRow;
    int col = cI.getCol() + dCol;
    int counter = 0;

    //Delta is 0 - no need to check anything, return an empty vector
    if (dRow == 0 && dCol == 0) {
        return potentialInPath;
    }

    //Run the path, using delta to advance in both directions
    for (; cellOnBoard(row, col); row += dRow, col += dCol) {
        //If an empty cell is reached, clear vector and return
        if (BOARD[row][col] == EMPTY) {
            potentialInPath.clear();
            return potentialInPath;
        }

        //If player's type is found, return
        if (BOARD[row][col] == type) {
            //if counter == 0, clear the vector
            if (counter == 0) { potentialInPath.clear(); }
            return potentialInPath;
        }

        //this point means that this cell is an opponent cell - add it!
        CellIndex opponentCell = {row, col};
        potentialInPath.push_back(opponentCell);
        counter++;
    }

    //check if last cell checked was out of bounds
    if (!cellOnBoard(row, col)) {
        potentialInPath.clear();
    }

    return potentialInPath;
}

/*
 * changeCellColor(CellIndex cI).
 *
 * @param cI CellIndex -- a struct representing a cell as { row,col }.
 *
 * The function will change the cell's value (color) on the board.
 */
void Board::changeCellColor(CellIndex cI) {
    //Local Variables
    int row = cI.getRow();
    int col = cI.getCol();
    Cell currentColor = this->board[row][col];

    this->board[row][col] = (Cell) ((bool) !currentColor);
}


/**
 * toString().
 *
 * @return a string representation of the current board
 */
std::string Board::toString() {
    std::string boardToString;

    std::string cols = colsNumbers();
    std::string separateLine = separatingLine();

    boardToString = cols;
    boardToString += separateLine;

    for (int i = 0; i < size; i++) {
        //row index and '|'
        boardToString += intToString(i + 1);
        boardToString += "|";
        for (int j = 0; j < size; j++) {
            std::string value = generateCellValue(getBoardCell(i, j));
            boardToString += " ";
            boardToString += value;
            boardToString += " ";
            boardToString += "|";
        }
        boardToString += "\n";
        boardToString += separatingLine();
    }
    boardToString += "\n";

    return boardToString;
}


/**
 * colsNumbers().
 *
 * @return a representation of col numbers as a string
 */
std::string Board::colsNumbers() {
    std::string str;
    //print first space and '|'
    str += " |";

    //Print cols numbers
    for (int i = 0; i < size; i++) {
        str += " ";
        str += intToString(i + 1);
        str += " ";
        str += "|";
    }

    //print closing '|' and end line
    str += "\n";

    return str;
}

/**
 * separatingLine().
 *
 * @return a seperating line as a string.
 */
std::string Board::separatingLine() {
    std::string str;

    //print first '-'
    str = "-";

    //print four '-' for every cell
    for (int i = 0; i < size; i++) {
        str += "----";
    }

    //print last '-' and end line
    str += "-";
    str += "\n";

    return str;
}
