// Author: Vaibhav Mahant

#ifndef PROBLEM_FUNCTIONS_HEADER
#define PROBLEM_FUNCTIONS_HEADER

#include <cmath>
#include <stack>
#include <vector>

#define NUMBER_OF_PLAYERS 2
#define MIN_POSITION_SCORE -100
#define MAX_POSITION_SCORE 100

using namespace std;

// Type Definitions
// ****************************************************************************
class position_type {
	// The game board is defined as a magic square:
	//  8 | 1 | 6
	// ---+---+---
	//  3 | 5 | 7
	// ---+---+---
	//  4 | 9 | 2

	// This maps the magic square to indicies (first row is 0, 1, 2; second is 3, 4, 5; third is 6, 7, 8
	int rowNumbers[9];
	int xOwned[5];
	int oOwned[5];
	int xOwnedNum;
	int oOwnedNum;

public:
	position_type() {
		rowNumbers[0] = 8;
		rowNumbers[1] = 1;
		rowNumbers[2] = 6;
		rowNumbers[3] = 3;
		rowNumbers[4] = 5;
		rowNumbers[5] = 7;
		rowNumbers[6] = 4;
		rowNumbers[7] = 9;
		rowNumbers[8] = 2;

		xOwnedNum = 0;
		oOwnedNum = 0;
	}

	// Updates the board to the new state
	void addMove(int movePos, int currentPlayer) {
		// 0: X
		if (currentPlayer == 0) {
			xOwned[xOwnedNum] = movePos;
			xOwnedNum++;
		}
		// 1: O
		else if (currentPlayer == 1) {
			oOwned[oOwnedNum] = movePos;
			oOwnedNum++;
		}
	}

	// Returns whether or not the game is finished (won or tied)
	bool gameIsOver() {
		return (getWinningPlayer() != -1) || (xOwnedNum + oOwnedNum == 9);
	}

	// Returns the number of the player who won based on this board
	int getWinningPlayer() {
		// X won?
		for (int x = 0; x < xOwnedNum; x++) {
			for (int y = x + 1; y < xOwnedNum; y++) {
				int neededTile = 15 - (xOwned[x] + xOwned[y]);
				if (ownedByPlayer(neededTile) == 0 && (neededTile != xOwned[x] && neededTile != xOwned[y])) {
					return 0;
				}
			}
		}
		// O won?
		for (int x = 0; x < oOwnedNum; x++) {
			for (int y = x + 1; y < oOwnedNum; y++) {
				int neededTile = 15 - (oOwned[x] + oOwned[y]);
				if (ownedByPlayer(neededTile) == 1 && (neededTile != oOwned[x] && neededTile != oOwned[y])) {
					return 1;
				}
			}
		}
		return -1;
	}

	// Returns the tile num for the win, or -1 if no winning move found
	int getWinningMove(int currentPlayer) {
		int ownedNum = (currentPlayer == 0) ? xOwnedNum : oOwnedNum;
		for (int x = 0; x < ownedNum; x++) {
			for (int y = x + 1; y < ownedNum; y++) {
				int tilesSum = (currentPlayer == 0) ? xOwned[x] + xOwned[y] : oOwned[x] + oOwned[y];
				int winningTile = 15 - tilesSum;
				if (ownedByPlayer(winningTile) == -1) {
					return winningTile;
				}
			}
		}
		return -1;
	}

	// Returns the number of rows, columns, and diagonals the given player can still win in
	int numWinnablePlaces(int currentPlayer) {
		int numPlaces = 0;

		// Rows
		for (int x = 0; x < 3; x++) {
			if ((ownedByPlayer(rowNumbers[x*3]) == currentPlayer || ownedByPlayer(rowNumbers[x*3]) == -1)
					&& (ownedByPlayer(rowNumbers[x*3+1]) == currentPlayer || ownedByPlayer(rowNumbers[x*3+1]) == -1)
					&& (ownedByPlayer(rowNumbers[x*3+2]) == currentPlayer || ownedByPlayer(rowNumbers[x*3+2]) == -1)) {
				numPlaces++;
			}
		}
		// Columns
		for (int x = 0; x < 3; x++) {
			if ((ownedByPlayer(rowNumbers[0+x]) == currentPlayer || ownedByPlayer(rowNumbers[0+x]) == -1)
					&& (ownedByPlayer(rowNumbers[3+x]) == currentPlayer || ownedByPlayer(rowNumbers[3+x]) == -1)
					&& (ownedByPlayer(rowNumbers[6+x]) == currentPlayer || ownedByPlayer(rowNumbers[6+x]) == -1)) {
				numPlaces++;
			}
		}
		// Diagonals
		if ((ownedByPlayer(rowNumbers[0]) == currentPlayer || ownedByPlayer(rowNumbers[0]) == -1)
				&& (ownedByPlayer(rowNumbers[4]) == currentPlayer || ownedByPlayer(rowNumbers[4]) == -1)
				&& (ownedByPlayer(rowNumbers[8]) == currentPlayer || ownedByPlayer(rowNumbers[8]) == -1)) {
			numPlaces++;
		}
		if ((ownedByPlayer(rowNumbers[2]) == currentPlayer || ownedByPlayer(rowNumbers[2]) == -1)
				&& (ownedByPlayer(rowNumbers[4]) == currentPlayer || ownedByPlayer(rowNumbers[4]) == -1)
				&& (ownedByPlayer(rowNumbers[6]) == currentPlayer || ownedByPlayer(rowNumbers[6]) == -1)) {
			numPlaces++;
		}

		return numPlaces;
	}
  // Returns one value, positive for advantage to one player, negative means advantage to the other. Zero indicates it is even.
    int numWithDesired(int currentPlayer, int opponentPlayer, int numMarkedDesired) {
		int numPlaces = 0;

		// Rows
		for (int x = 0; x < 3; x++) {
               int currentCount = 0;
               int opponentCount = 0;
        if (ownedByPlayer(rowNumbers[x*3]) == currentPlayer){
            currentCount ++;
            }
        if (ownedByPlayer(rowNumbers[3+x]) == currentPlayer){
            currentCount ++;
            }
         if (ownedByPlayer(rowNumbers[x*3+2]) == currentPlayer){
            currentCount ++;
            }
		if (ownedByPlayer(rowNumbers[x*3]) == opponentPlayer){
            opponentCount ++;
            }
        if (ownedByPlayer(rowNumbers[3+x]) == opponentPlayer){
            opponentCount ++;
            }
		 if (ownedByPlayer(rowNumbers[x*3+2]) == opponentPlayer){
            opponentCount ++;
            }
         if(currentCount == numMarkedDesired && opponentCount == 0){
            numPlaces ++;
         }
		}
		// Columns
		for (int x = 0; x < 3; x++) {
               int currentCount = 0;
               int opponentCount = 0;
        if (ownedByPlayer(rowNumbers[0+x]) == currentPlayer){
            currentCount ++;
            }
        if (ownedByPlayer(rowNumbers[x*3+1]) == currentPlayer){
            currentCount ++;
            }
         if (ownedByPlayer(rowNumbers[6+x]) == currentPlayer){
            currentCount ++;
            }
		if (ownedByPlayer(rowNumbers[0+x]) == opponentPlayer){
            opponentCount ++;
            }
        if (ownedByPlayer(rowNumbers[x*3+1]) == opponentPlayer){
            opponentCount ++;
            }
		 if (ownedByPlayer(rowNumbers[6+x]) == opponentPlayer){
            opponentCount ++;
            }
         if(currentCount == numMarkedDesired && opponentCount == 0){
            numPlaces ++;
         }
		}

		// Diagonals
		int currentCount = 0;
		int opponentCount = 0;
		if (ownedByPlayer(rowNumbers[0]) == currentPlayer){
            currentCount ++;
            }
        if (ownedByPlayer(rowNumbers[4]) == currentPlayer){
            currentCount ++;
            }
         if (ownedByPlayer(rowNumbers[8]) == currentPlayer){
            currentCount ++;
            }
		if (ownedByPlayer(rowNumbers[0]) == opponentPlayer){
            opponentCount ++;
            }
        if (ownedByPlayer(rowNumbers[4]) == opponentPlayer){
            opponentCount ++;
            }
		 if (ownedByPlayer(rowNumbers[8]) == opponentPlayer){
            opponentCount ++;
            }
         if(currentCount == numMarkedDesired && opponentCount == 0){
            numPlaces ++;
         }
          currentCount = 0;
          opponentCount = 0;
         if (ownedByPlayer(rowNumbers[2]) == currentPlayer){
            currentCount ++;
            }
        if (ownedByPlayer(rowNumbers[4]) == currentPlayer){
            currentCount ++;
            }
         if (ownedByPlayer(rowNumbers[6]) == currentPlayer){
            currentCount ++;
            }
		if (ownedByPlayer(rowNumbers[2]) == opponentPlayer){
            opponentCount ++;
            }
        if (ownedByPlayer(rowNumbers[4]) == opponentPlayer){
            opponentCount ++;
            }
		 if (ownedByPlayer(rowNumbers[6]) == opponentPlayer){
            opponentCount ++;
            }
         if(currentCount == numMarkedDesired && opponentCount == 0){
            numPlaces ++;
         }


		return numPlaces;
	}
	// Returns the player number who owns the given tile (or -1 if none)
	int ownedByPlayer(int tileNum) {
		// Make sure tile given is inside board bounds
		if (tileNum < 1 || tileNum > 9) {
			return -2;
		}
		for (int y = 0; y < xOwnedNum; y++) {
			if (xOwned[y] == tileNum) {
				return 0;
			}
		}
		for (int y = 0; y < oOwnedNum; y++) {
			if (oOwned[y] == tileNum) {
				return 1;
			}
		}
		return -1;
	}

	// Prints out the physical representation of the board
	string toString() {
		string representation = "";
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (ownedByPlayer(rowNumbers[x*3+y]) == 0) {
					representation += " X ";
				}
				else if (ownedByPlayer(rowNumbers[x*3+y]) == 1) {
					representation += " O ";
				}
				else if (ownedByPlayer(rowNumbers[x*3+y]) == -1) {
					representation += "   ";
				}
				if (y != 2) {
					representation += "|";
				}
				else {
					representation += "\n";
				}
			}
			if (x != 2) {
				representation += "---+---+---\n";
			}
		}
		return representation;
	}
};
struct return_type {
	int value;
	stack<position_type> path;
};

// Function Prototypes
// ****************************************************************************
bool deepEnough(position_type currentPosition, int currentDepth);
vector<position_type> moveGen(position_type currentPosition, int currentPlayer);
int getNextPlayer(int currentPlayer);
int positionEvaluation(position_type currentPosition, int currentPlayer);

#endif
