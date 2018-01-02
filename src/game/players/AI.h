/*
 * Project:    Ex4.
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

#ifndef AI_H_
#define AI_H_

//----------INCLUDING----------
#include <string>
#include <iostream>
#include <unistd.h>

#include "Player.h"
#include "../board/Cell.h"
#include "../../display/Display.h"
#include "../game_logic/MovesEvaluator.h"

//----------DEFINITIONS----------
#define INT_MAX 2147483647
#define AI_COLOR (Cell) Player::getValue()
#define PLAYER_COLOR (Cell) !AI_COLOR

using namespace std;

class AI : public Player, public MovesEvaluator {
public:
    //----------PUBLIC FUNCTIONS----------
    // Initialize
    explicit            AI(Board* gameBoard);

    // Destructor
    ~AI();

    // In-game Use
    virtual CellIndex*  makeAMove(vector<CellIndex> aMoves)         const;

private:
    //----------PRIVATE FUNCTIONS----------
	// Utility
    int                 calculatePotential(
                            Board *gb, vector<CellIndex> vec)       const;
};

#endif /* AI_H_ */
