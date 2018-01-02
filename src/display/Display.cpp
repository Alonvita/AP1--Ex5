/**
 * Project:    Ex5.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class Display.
 *
 */

#include "Display.h"

/**
 * printBoard().
 */
void printBoard(Board *b) {
    // Local Variables
    int size = b->getSize();

    cout << endl << "The current board state is:" << endl << endl;

    std::string colsNumbers = b->colsNumbers();
    std::string separatingLine = b->separatingLine();

    //print first two rows
    cout << colsNumbers;
    cout << separatingLine;

    //Print array by rows WITH numbers
    for (int i = 0; i < size; i++) {
        cout << i + 1 << "|"; //row index and '|'
        for (int j = 0; j < size; j++) {
            cout << " " <<
                 b->generateCellValue(b->getBoardCell(i, j))
                 << " " << "|";
        }
        cout << endl;
        cout << b->separatingLine();
    }
    cout << endl;
}


//---------- TURNS MANAGER DISPLAY ----------
/**
 * turnEndedMessage().
 */
void turnEndedMessage() {
    cout << endl << "Turn has Ended" << endl;
}

/**
 * illegalMove().
 */
void illegalMove() {
    cout << "This move is illegal" << endl << endl;
}

//---------- GAME DISPLAY ----------
/**
 * gameEnded().
 */
void gameEndedAnnouncement() {
    //Ending announcement
    cout << "The game has ended!" << endl << endl;
}

/**
 * announceWinner().
 *
 * This function calculates the board's status and returns the winner.
 */
void announceWinner(Board *gb) {
    //Local Variables
    int *scores = gb->evaluateFinalScore(); //get scores array
    int winnerScore;
    bool winner;

    if (scores[0] > scores[1]) {
        winnerScore = scores[0];
        winner = 0;
    } else if (scores[0] < scores[1]) {
        winnerScore = scores[1];
        winner = 1;
    } else {
        cout << "!WE HAVE A TIE!";
        delete scores;
        return;
    }

    cout << "The winner is: " << generatePlayerName(winner) <<
         " with " << winnerScore << " points. Over " <<
         generatePlayerName(!winner) << " with " <<
         pow(gb->getSize(), 2) - winnerScore << " points" << endl;

    delete scores;
}

//---------- PLAYER DISPLAY ----------
/**
 * generatePlayerName(bool b).
 *
 * @param bool b -- a boolean representing true/false so that true is
 *                   white false is black.
 *
 * @return string representing player's name
 */
string generatePlayerName(bool b) {
    if (b == 0) { return "WHITE"; }
    return "BLACK";
}

/**
 * printAvailableMoves(vector<CellIndex> aMoves) const.
 *
 * @param aMoves vector<CellIndex> -- a vector of available moves.
 */
void printAvailableMoves(vector<CellIndex> aMoves) {
    //Print
    cout << "the possible moves for your turn are: " << endl;

    //Iter over available moves and print them
    for (unsigned i = 0; i < aMoves.size(); ++i) {
        cout << "(" << aMoves[i].getRow() + 1
             << "," << aMoves[i].getCol() + 1 << ")";
        if (i != aMoves.size() - 1) {
            cout << ",";
        }
    }
    cout << endl;
}

/**
 * makeAMoveAnnouncement().
 */
void makeAMoveAnnouncement() {
    cout << " player, Please make a move row,col:" << endl;
}


/**
 * aiMove(CellIndex bMove).
 *
 * @param bMove CellIndex -- a move to print.
 */
void printAIMove(CellIndex bMove) {
    cout << "Alright... my move is: ";
    cout << "(" << bMove.getRow() + 1
         << "," << bMove.getCol() + 1 << ")" << endl;
}

//---------- SERVER DISPLAY ----------
/**
 * announcePlayerColor(int playerTurn).
 *
 * @param playerTurn bool -- a player turn as boolean: WHITE = 1 BLACK = 0
 */
void announcePlayerColor(bool playerTurn) {
    cout << "You are the " << generatePlayerName(playerTurn) << " Player!";
}

/**
 * void clientCreatedAnnouncement().
 */
void clientCreatedAnnouncement() {
    cout << "ServerClient Created" << endl;
}

/**
 * socketOpenSuccess().
 */
void socketOpenSuccess() {
    cout << ">> Successfully opened socket." << endl;
}

/**
 * initializingSocketAnnouncement().
 */
void initializingSocketAnnouncement() {
    cout << "Initializing Socket..." << endl;
}

/**
 * serverListeningAnnouncement(int port).
 *
 * @param port int -- the port that the server is listening to.
 */
void serverListeningAnnouncement(int port) {
    cout << ">> Server is listening on port: " << port << "." << endl;
    cout << "Finished initializing the socket." << endl << endl;
}