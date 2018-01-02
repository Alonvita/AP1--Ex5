/*
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * ReversiGame Class.
 *
 * The ReversiGame class is in charge of starting and ending a game.
 */

#include "Reversi.h"

//----------Initializer List----------
/*
 * Reversi(board* gb) Constructor.
 *
 * @param gb board* -- a reference to the game's board.
 */
Reversi::Reversi(int boardType, int gameMode) {
    this->gameBoard = new Board(boardType);
    this->isGameOnline = isGameOnline;
    initializeTurnsManager((GameMode) gameMode);
}

//----------DESTRUCTORS----------
/*
 * Reversi */
Reversi::~Reversi() {
    delete this->manager;
    delete this->gameBoard;
    delete this;
}

//----------INITIALIZING FUNCTIONS----------
/* initializeTurnsManager().
 *
 * This function will scan a number of players from the player and create the
 *  turns manager accordingly.
 */
void Reversi::initializeTurnsManager(enum GameMode gameMode) {
    // Local Variables
    int numberOfPlayers;

    numberOfPlayers = gameMode == ONE_PLAYER ? 1 : 2;

    manager = new TurnsManager(numberOfPlayers, gameBoard);
}

//----------PUBLIC FUNCTIONS----------
//----------IN-GAME USE-----------
/* startGame().
 *
 * This function will start the game and handle the game flow.
 */
void Reversi::startGame() {
    // Print the board
    printBoard(this->gameBoard);

    while ((GAME_BOARD.getSpaceLeft())) {
        // Generate a game move
        gameMove();

        //Print the board
        printBoard(this->gameBoard);
    }
    endGame();
}

/*
 * gameMove().
 */
void Reversi::gameMove() {
    // Evaluate available moves for player
    MANAGER->evaluateAvailableMovesForThisTurn(this->gameBoard);

    // End turn if player has no available moves
    if (MANAGER->getAvailableMovesNum() == 0) {
        MANAGER->endTurn();
    } else {
        // Nested Functions explanation: moveMade (board) calls:
        //  1). nextMove (manager) -> CellIndex
        //  2). getCurrentPlayerColor (manager) -> Cell
        GAME_BOARD.moveMade(MANAGER->nextMove(),
                            MANAGER->getCurrentPlayerColor());
        MANAGER->endTurn();
    }
}

/* endGame().
 *
 * This function will end the game and call announceWinner().
 */
void Reversi::endGame() {
    // print game ended announcement
    gameEndedAnnouncement();

    //Print board
    printBoard(this->gameBoard);

    //Announce Winner
    announceWinner(this->gameBoard);
}