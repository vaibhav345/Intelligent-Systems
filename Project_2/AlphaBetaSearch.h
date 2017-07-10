// Author: Vaibhav Mahant

#ifndef ALPHA_BETA_HEADER
#define ALPHA_BETA_HEADER

#include "ProblemFunctions.h"

// Function Prototypes
// ****************************************************************************
template<typename T> return_type maxValue(T currentPosition, int currentPlayer, int depth, int alpha, int beta, int *total);
template<typename T> return_type minValue(T currentPosition, int currentPlayer, int depth, int alpha, int beta, int *total);

// Algorithm Functions
// ****************************************************************************
template<typename T>
return_type alphaBetaSearch(T currentPosition, int currentPlayer, int *total) {
	int depth = 0;
	return_type maxPosition = maxValue(currentPosition, currentPlayer, depth, MIN_POSITION_SCORE, MAX_POSITION_SCORE, total);
	return maxPosition;
}

// Finds the maximum valued path of the minimum paths of all of its children
template<typename T>
return_type maxValue(T currentPosition, int currentPlayer, int depth, int alpha, int beta, int *total) {
	// End the recursion
	if (deepEnough(currentPosition, depth)) {
		return_type returnInfo;
		returnInfo.value = positionEvaluation(currentPosition, currentPlayer);
		stack<T> path;
		returnInfo.path = path;
		return returnInfo;
	}

	// Find the maximum child path
	int value = MIN_POSITION_SCORE;
	vector<T> actionResult = moveGen(currentPosition, currentPlayer);
	stack<T> bestPosition;
	for (int i = 0; i < actionResult.size(); i++) {
		(*total)++;
		// Recursive call
		return_type minPosition = minValue(actionResult[i], currentPlayer, depth + 1, alpha, beta, total);
		if (minPosition.value > value) {
			bestPosition = minPosition.path;
			bestPosition.push(actionResult[i]);
			value = minPosition.value;
		}
		// Discard this branch for being out of bounds
		if (value >= beta){
			return_type returnInfo;
			returnInfo.value = value;
			returnInfo.path = bestPosition;
			return returnInfo;
		}
		alpha = max(alpha, value);
	}
	return_type returnInfo;
	returnInfo.value = value;
	returnInfo.path = bestPosition;
	return returnInfo;
}

// Finds the minimum valued path of the maximum paths of all of its children
template<typename T>
return_type minValue(T currentPosition, int currentPlayer, int depth, int alpha, int beta, int *total) {
	// End the recursion
	if (deepEnough(currentPosition, depth)) {
		return_type returnInfo;
		returnInfo.value = positionEvaluation(currentPosition, currentPlayer);
		stack<T> path;
		returnInfo.path = path;
		return returnInfo;
	}

	// Find the minimum child path
	int value = MAX_POSITION_SCORE;
	vector<T> actionResult = moveGen(currentPosition, getNextPlayer(currentPlayer));
	stack<T> bestPosition;
	for (int i = 0; i < actionResult.size(); i++) {
		(*total)++;
		// Recursive call
		return_type maxPosition = maxValue(actionResult[i], currentPlayer, depth + 1, alpha, beta, total);
		if (maxPosition.value < value) {
			bestPosition = maxPosition.path;
			bestPosition.push(actionResult[i]);
			value = maxPosition.value;
		}
		// Discard this branch for being out of bounds
		if (value <= alpha) {
			return_type returnInfo;
			returnInfo.value = value;
			returnInfo.path = bestPosition;
			return returnInfo;
		}
		beta = min(beta, value);
	}
	return_type returnInfo;
	returnInfo.value = value;
	returnInfo.path = bestPosition;
	return returnInfo;
}

#endif
