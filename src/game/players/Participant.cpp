/**
 * Project:    Ex5.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Participant Class.
 *
 * A Participant is an outside user.
 */

#include "Participant.h"

//----------Initializer List----------
/*
 * Participant(Cell c) Constructor.
 *
 * @param c Cell -- participant's color
 */
Participant::Participant(Cell c) : Player(c) {}

//----------Public Functions----------
/*
 * makeMove().
 *
 * @return CellIndex -- a CellIndex representing Participant's move.
 */
CellIndex* Participant::makeAMove(vector<CellIndex> aMoves) const {
    //Local Variables
    string rawPlayerString;

    //Print
    generatePlayerName(this->getValue());
    printAvailableMoves(aMoves);
    makeAMoveAnnouncement();

    cin >> rawPlayerString;

    CellIndex* returnVal = new CellIndex();
    returnVal->fromString(rawPlayerString);

    return (returnVal);
}