/**
 * Project:    Ex5.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class Display.
 *
 */
#ifndef AP1_EX3_DISPLAY_H
#define AP1_EX3_DISPLAY_H

#include <string>
#include <iostream>
#include <sstream>

#include "../game/board/Board.h"

using namespace std;

//---------- BOARD DISPLAY ----------
void        printBoard(Board* b);
//---------- TURNS MANAGER DISPLAY ----------
void turnEndedMessage();
void illegalMove();

//---------- GAME DISPLAY ----------
void gameEndedAnnouncement();
void announceWinner(Board* gb);
string generatePlayerName(bool b);

//---------- PLAYER DISPLAY ----------
void printAvailableMoves(vector<CellIndex> aMoves);
void makeAMoveAnnouncement();
void printAIMove(CellIndex bMove);

//---------- SERVER DISPLAY ----------
void announcePlayerColor(bool playerTurn);
void clientCreatedAnnouncement();
void socketOpenSuccess();
void initializingSocketAnnouncement();
void serverListeningAnnouncement(int port);

#endif //AP1_EX3_DISPLAY_H
