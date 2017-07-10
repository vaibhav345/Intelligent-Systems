// Author: Terry Penner
// Date Created: Sept. 1, 2014
// File name: Project1-A04367972.cpp
// Purpose: To be the front-end for the backwards and forwards chaining algorithms
// Usage: g++ Project1-A04367972.cpp KnowledgeBase.cpp BackwardsChaining.cpp ForwardsChaining.cpp

#include <iostream>
#include <cerrno>
#include "BackwardsChaining.h"
#include "ForwardsChaining.h"

using namespace std;

int main() {
	// Backwards Chaining
	// ************************************************************************
	string conclusion = "CRISIS";
	string backwardsResult = runBackwardsChaining(conclusion);

	// Print result
	cout << endl;
	if (!backwardsResult.empty()) {
		cout << conclusion << " was found to be " << backwardsResult << "." << endl;
	}
	else {
		cout << "The value of " << conclusion << " could not be found." << endl;
	}
	cout << endl;

	// Forwards Chaining
	// ************************************************************************
	conclusion_type foundConclusions = runForwardsChaining(conclusion, backwardsResult);

	// Print result
	cout << endl;
	cout << "The following additional conclusions were found:" << endl;
	if (foundConclusions.size() > 0) {
		for (unsigned int x = 0; x < foundConclusions.size(); x++) {
			cout << foundConclusions[x].first << ": " << foundConclusions[x].second << endl;
		}
	}
	else {
		cout << "NONE" << endl;
	}

	return 0;
}

// Required from KnowledgeBase.h, through BackwardsChaining.h and ForwardsChaining.h
string getUserInput(string prompt, const vector<string> &acceptedValues) {
	string result;
	bool valid = false;
	bool canHaveNumber = false;

	// Repeat getting the user's input until it is valid
	do {
		// Prompting the user for their input, listing all accepted values
		cout << prompt << " (";
		for (vector<string>::const_iterator acceptedValue = acceptedValues.begin(); acceptedValue != acceptedValues.end(); acceptedValue++) {
			if (acceptedValue != acceptedValues.begin()) {
				cout << ", ";
			}
			cout << *acceptedValue;
			canHaveNumber = equalsIgnoreCase(*acceptedValue, "#");
		}
		cout << "): ";

		// Reading in the user's input
		cin >> result;

		// Make sure the input string is in the acceptable list
		for (vector<string>::const_iterator acceptedValue = acceptedValues.begin(); acceptedValue != acceptedValues.end(); acceptedValue++) {
			if (equalsIgnoreCase(*acceptedValue, result)) {
				valid = true;
				result = *acceptedValue;
				break;
			}
		}
		if (canHaveNumber) {
			// Make sure the input is a valid float number
			const char *input = result.c_str();
			char *end;
			strtof(input, &end);
			if (end != input && *end == '\0' && errno != ERANGE) {
				valid = true;
			}
		}
	} while (!valid);

	return result;
}
