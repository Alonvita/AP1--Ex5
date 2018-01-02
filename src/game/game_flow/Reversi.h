/*
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * ReversiGame Class.
 *
 * The ReversiGame class is in charge of starting and ending a game.
 */

#ifndef REVERSIGAME_H_
#define REVERSIGAME_H_


//----------INCLUDING----------
#include <string>
#include "../board/Board.h"
#include "../game_logic/TurnsManager.h"
#include "../../display/Display.h"

//----------DEFINITIONS----------
#define GAME_BOARD (*(this->gameBoard))
#define MANAGER this->manager

enum GameMode { TWO_PLAYERS = 1, ONE_PLAYER = 2};

class Reversi {
public:
    //----------PUBLIC FUNCTIONS----------
    // Initialize
    Reversi(int boardType, int gameType);

    // Destruct
    ~Reversi();

    // Utility
    void                startGame();

private:
    //----------VARIABLES----------
    Board* 				gameBoard;
    TurnsManager* 		manager;
    int                 isGameOnline;

    //----------PRIVATE FUNCTIONS----------
    // Initialization
    void                initializeTurnsManager(enum GameMode gameMode);

    // In-game Use
    void                endGame();
    void                gameMove();
};


#endif /* REVERSIGAME_H_ */
