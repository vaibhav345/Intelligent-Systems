// Author: Vaibhav Mahant

#ifndef MINMAXAB_HEADER
#define MINMAXAB_HEADER

#include "ProblemFunctions.h"

// Algorithm Functions
// ****************************************************************************
template<typename T>
return_type minMaxAB(T currentPosition, int depth, int currentPlayer, int useThresh, int passThresh, int *total) {
	// End the recursion
	if (deepEnough(currentPosition, depth)) {
		return_type staticInfo;
		staticInfo.value = positionEvaluation(currentPosition, currentPlayer);
		stack<T> path;
		staticInfo.path = path;
		return staticInfo;
	}

	// Find the best of all child paths
	vector<T> succ = moveGen(currentPosition, currentPlayer);
	if (succ.size() == 0){
		return_type staticInfo;
		staticInfo.value = positionEvaluation(currentPosition, currentPlayer);
		stack<T> path;
		staticInfo.path = path;
		return staticInfo;
	}
	stack<T> bestPath;
	for(int i = 0; i < succ.size(); i++) {
		(*total)++;
		// Recursive call
		return_type resultSuccessors = minMaxAB(succ[i], depth + 1, getNextPlayer(currentPlayer), -passThresh, -useThresh, total);
		int newValue = -resultSuccessors.value;
		if(newValue > passThresh) {
			passThresh = newValue;
			bestPath = resultSuccessors.path;
			bestPath.push(succ[i]);
		}
		// Discard this branch for being out of bounds
		if(passThresh >= useThresh){
			return_type info ;
			info.value = passThresh;
			info.path = bestPath;
			return info;
		}
	}

	return_type info;
	info.value = passThresh;
	info.path = bestPath;
	return info;
}

#endif
