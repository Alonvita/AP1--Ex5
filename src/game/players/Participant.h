/*
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Participant Class.
 *
 * A Participant is an out side user.
 *
 */

#ifndef PLAYER_H_
#define PLAYER_H_

//----------INCLUDING----------
#include <string>
#include <iostream>
#include <sstream>

#include "Player.h"
#include "../board/Cell.h"
#include "../../display/Display.h"

using namespace std;

class Participant : public Player {
public:
    //----------PUBLIC FUNCTIONS----------
    // Initialize
    explicit            Participant(Cell c);
    // In-game Use
    virtual CellIndex*  makeAMove(vector<CellIndex> aMoves) const;
};

#endif /* PLAYER_H_ */
