// Author: Vaibhav Mahant

#include <cstdlib>
#include <iostream>
#include "MinMaxAB.h"
#include "AlphaBetaSearch.h"

using namespace std;

// Function Prototypes
// ****************************************************************************
void runAlgorithm(int algorithmChoice);
int positionEvaluationInClass(position_type currentPosition, int currentPlayer);
int positionEvaluationAlakhA(position_type currentPosition, int currentPlayer);
int positionEvaluationAlakhN(position_type currentPosition, int currentPlayer);
int positionEvaluationTerryA(position_type currentPosition, int currentPlayer);
int positionEvaluationTerryN(position_type currentPosition, int currentPlayer);
int positionEvaluationVaibhavA(position_type currentPosition, int currentPlayer);
int positionEvaluationVaibhavN(position_type currentPosition, int currentPlayer);

// Global Variables
// ****************************************************************************
int cutoffDepth = 0;
int evaluationFunction = 0;

// Main Methods
// ****************************************************************************
int main() {
	// User input for program parameters
	int algorithmChoice = 0;
	cout << "Which look-ahead algorithm would you like to use?" << endl;
	cout << "[1] Min Max A-B" << endl;
	cout << "[2] Alpha-Beta Search" << endl;
	cout << "Enter choice: ";
	cin >> algorithmChoice;
	while (algorithmChoice != 1 && algorithmChoice != 2) {
		cout << "Please enter a valid choice [1,2]: ";
		cin >> algorithmChoice;
	}
	cout << endl;
	cout << "What cutoff depth would you like to use? [2-10]: ";
	cin >> cutoffDepth;
	while (cutoffDepth < 2 || cutoffDepth > 10) {
		cout << "Please enter a valid choice [2-10]: ";
		cin >> cutoffDepth;
	}
	cout << endl;
	cout << "What evaluation function would you like to use?" << endl;
	cout << "[1] In-Class" << endl;
	cout << "[2] Admissable-A" << endl;
	cout << "[3] Nonadmissable-B" << endl;
	cout << "[4] Admissable-C" << endl;
	cout << "[5] Nonadmissable-D" << endl;
	cout << "[6] Admissable-E" << endl;
	cout << "[7] Nonadmissable-F" << endl;
	cout << "Enter choice: ";
	cin >> evaluationFunction;
	while (evaluationFunction < 1 || evaluationFunction > 7) {
		cout << "Please enter a valid choice [1-7]: ";
		cin >> evaluationFunction;
	}

	// Run chosen algorithm
	runAlgorithm(algorithmChoice);

	return 0;
}

// Function to run the alpha beta pruning
void runAlgorithm(int algorithmChoice) {
	position_type currentPosition;
	int currentPlayer = 0;

	if (algorithmChoice == 1) {
		cout << "Min Max A-B" << endl;
	}
	else if (algorithmChoice == 2) {
		cout << "Alpha Beta Search" << endl;
	}
	int totalNodes = 0;
	int prevTotalNodes = 0;
	int pathLen = 0;
	while (!currentPosition.gameIsOver()) {
		if (currentPlayer == 0) {
			cout << "Player: X" << endl;
		}
		else if (currentPlayer == 1) {
			cout << "Player: O" << endl;
		}

		// Run the specified alpha beta pruning algorithm and print results
		return_type bestMove;
		if (algorithmChoice == 1) {
			bestMove = minMaxAB<position_type>(currentPosition, 0, currentPlayer, MAX_POSITION_SCORE, MIN_POSITION_SCORE, &totalNodes);
		}
		else if (algorithmChoice == 2) {
			bestMove = alphaBetaSearch<position_type>(currentPosition, currentPlayer, &totalNodes);
		}
		cout << currentPosition.toString();
		cout << "Best Value: " << bestMove.value << endl;
		cout << "Nodes for move: " << (totalNodes - prevTotalNodes) << endl;
		prevTotalNodes = totalNodes;

		// Output the projected path
		currentPosition = bestMove.path.top();
		currentPlayer = getNextPlayer(currentPlayer);
		while (!bestMove.path.empty()) {
			cout << bestMove.path.top().toString() << endl;
			bestMove.path.pop();
		}
		pathLen++;
	}

	// Print final result
	cout << endl;
	if (currentPosition.getWinningPlayer() == 0) {
		cout << "Player X Won!" << endl;
	}
	else if (currentPosition.getWinningPlayer() == 1) {
		cout << "Player O Won!" << endl;
	}
	else {
		cout << "Draw" << endl;
	}
	cout << "Total nodes: " << totalNodes << endl;
	cout << "Path length: " << pathLen << endl;
}

// Methods From ProblemFunctions.h
// ****************************************************************************
bool deepEnough(position_type currentPosition, int depth) {
	return (depth > cutoffDepth - 1) || currentPosition.gameIsOver();
}

vector<position_type> moveGen(position_type currentPosition, int currentPlayer) {
	vector<position_type> children;
	for (int x = 1; x < 10; x++) {
		position_type child = currentPosition;
		if (child.ownedByPlayer(x) == -1) {
			child.addMove(x, currentPlayer);
			children.push_back(child);
		}
	}
	return children;
}

int getNextPlayer(int currentPlayer) {
	return (currentPlayer + 1) % NUMBER_OF_PLAYERS;
}

// Calls the requested evaluation function
int positionEvaluation(position_type currentPosition, int currentPlayer) {
	switch(evaluationFunction) {
	case 1:
		return positionEvaluationInClass(currentPosition, currentPlayer);
	case 2:
		return positionEvaluationAlakhA(currentPosition, currentPlayer);
	case 3:
		return positionEvaluationAlakhN(currentPosition, currentPlayer);
	case 4:
		return positionEvaluationTerryA(currentPosition, currentPlayer);
	case 5:
		return positionEvaluationTerryN(currentPosition, currentPlayer);
	case 6:
		return positionEvaluationVaibhavA(currentPosition, currentPlayer);
	case 7:
		return positionEvaluationVaibhavN(currentPosition, currentPlayer);
	default:
		return positionEvaluationInClass(currentPosition, currentPlayer);
	}
}

// In-class
// Returns the number of places the current player can win minus the number of places the next player can win
int positionEvaluationInClass(position_type currentPosition, int currentPlayer) {
	return currentPosition.numWinnablePlaces(currentPlayer) - currentPosition.numWinnablePlaces(getNextPlayer(currentPlayer));
}

// Alakh: Admissable
int positionEvaluationAlakhA(position_type currentPosition, int currentPlayer) {
    int currentCountOne = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 1);
    int currentCountTwo = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 2);
    int currentCountThree = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 3);
    int opponentCountOne = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 1);
    int opponentCountTwo = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 2);
    int opponentCountThree = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 3);
     if (currentCountOne + currentCountTwo + currentCountThree > opponentCountOne + opponentCountTwo + currentCountThree){
        return 1;
    }
     if (currentCountOne + currentCountTwo + currentCountThree < opponentCountOne + opponentCountTwo + currentCountThree){
        return -1;
    }
    return 0;

}

// Alakh: Non-Admissable
int positionEvaluationAlakhN(position_type currentPosition, int currentPlayer) {
    int currentCountOne = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 1);
    int currentCountTwo = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 2);
    int currentCountThree = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 3);
    int opponentCountOne = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 1);
    int opponentCountTwo = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 2);
    int opponentCountThree = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 3);

	return (10*currentCountThree+5*currentCountTwo+currentCountOne-(10*opponentCountThree+5*opponentCountTwo+opponentCountOne));
}

// Terry: Admissable
// Returns 1 if current can win, -1 if next can win, 0 otherwise
int positionEvaluationTerryA(position_type currentPosition, int currentPlayer) {
	if (currentPosition.getWinningPlayer() == currentPlayer) {
		return 1;
	}
	if (currentPosition.getWinningPlayer() == getNextPlayer(currentPlayer)) {
		return -1;
	}
	return 0;
}

// Terry: Non-Admissable
// Returns max if current can win, min if next can win, difference in number of winnable places otherwise
int positionEvaluationTerryN(position_type currentPosition, int currentPlayer) {
	if (currentPosition.getWinningPlayer() == currentPlayer) {
		return MAX_POSITION_SCORE - 1;
	}
	if (currentPosition.getWinningPlayer() == getNextPlayer(currentPlayer)) {
		return MIN_POSITION_SCORE + 1;
	}
	return currentPosition.numWinnablePlaces(currentPlayer) - currentPosition.numWinnablePlaces(getNextPlayer(currentPlayer));
}

// Vaibhav: Admissable
int positionEvaluationVaibhavA(position_type currentPosition, int currentPlayer) {
    int currentCountOne = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 1);
    int currentCountTwo = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 2);
    int opponentCountOne = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 1);
    int opponentCountTwo = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 2);
    if (currentCountOne + currentCountTwo > opponentCountOne + opponentCountTwo){
        return 1;
    }
     if (currentCountOne + currentCountTwo < opponentCountOne + opponentCountTwo){
        return -1;
    }
    return 0;
}

// Vaibhav: Non-Admissable
int positionEvaluationVaibhavN(position_type currentPosition, int currentPlayer) {
        if (currentPosition.getWinningPlayer() == currentPlayer) {
		return MAX_POSITION_SCORE - 1;
	}
	if (currentPosition.getWinningPlayer() == getNextPlayer(currentPlayer)) {
		return MIN_POSITION_SCORE + 1;
	}
    int currentCountOne = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 1);
    int currentCountTwo = currentPosition.numWithDesired(currentPlayer,getNextPlayer(currentPlayer), 2);
    int opponentCountOne = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 1);
    int opponentCountTwo = currentPosition.numWithDesired(getNextPlayer(currentPlayer),currentPlayer, 2);
	return 3*currentCountTwo + currentCountOne - (3*opponentCountTwo + opponentCountOne);
}
