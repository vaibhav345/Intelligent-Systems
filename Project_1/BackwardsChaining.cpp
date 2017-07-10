// Author: Terry Penner
// Date Created: Sept. 1, 2014
// File name: BackwardsChaining.cpp
// Purpose: To perform the backwards chaining algorithm
// Usage: See Project1-A04367972.cpp

#include "BackwardsChaining.h"

// This function attempts to find the value of the given conclusion based on the rules it appears in
void findValue(const string &conclusion, variable_type &variableMap, const clause_type &clauseVariableList, const conclusion_type &conclusionList) {
	for (unsigned int x = 0; x < conclusionList.size(); x++) {
		if (equalsIgnoreCase(conclusionList[x].first, conclusion)) {
			for (unsigned int y = 0; y < clauseVariableList[x].size(); y++) {
				string currentVariable = clauseVariableList[x][y].first;
				// Fill variables
				// If variable is an uninitialized conclusion
				if (variableMap.count(currentVariable) == 0) {
					// Recursive call to simulate variable stack
					findValue(currentVariable, variableMap, clauseVariableList, conclusionList);
				}
				// If variable is uninitialized
				else if (!variableMap[currentVariable].isInitialized) {
					variableMap[currentVariable].value = getUserInput(variableMap[currentVariable].prompt, variableMap[currentVariable].acceptedValues);
					variableMap[currentVariable].isInitialized = true;
				}

				// Check variables
				// If variable is initialized
				if (variableMap.count(currentVariable) > 0 && variableMap[currentVariable].isInitialized) {
					// If variable's value does not match the rule's requirement, give up on rule
					if (!equalsIgnoreCase(variableMap[currentVariable].value, clauseVariableList[x][y].second)) {
						break;
					}
					// If all clauses in rule match, assign value to conclusion
					else if (y == clauseVariableList[x].size() - 1) {
						variableMap[conclusion].value = conclusionList[x].second;
						variableMap[conclusion].isInitialized = true;
						return;
					}
				}
				// If variable is still uninitialized, give up on rule
				else {
					break;
				}
			}
		}
	}
}

// This method is the main access point for starting the backwards chaining process
string runBackwardsChaining(const string &conclusion) {
	conclusion_type conclusionList;
	variable_type variableMap;
	clause_type clauseVariableList;

	// Filling data structures
	readKnowledgeBase(BACKWARDS_KNOWLEDGE_BASE, conclusionList, variableMap, clauseVariableList);

	// Backwards Chaining
	findValue(conclusion, variableMap, clauseVariableList, conclusionList);
	string result = variableMap[conclusion].value;

	/* Debug output
	cout << "VARIABLES VALUES:" << endl;
	for (map<string, variableInfo>::iterator variable = variableMap.begin(); variable != variableMap.end(); variable++) {
		cout << variable->first << ": " << variable->second.value << endl;
	}
	*/

	return result;
}
