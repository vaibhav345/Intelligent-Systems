// Author: Terry Penner
// Date Created: Sept. 1, 2014
// File name: ForwardsChaining.cpp
// Purpose: To perform the forwards chaining algorithm
// Usage: See Project1-A04367972.cpp

#include "ForwardsChaining.h"

// This method takes the variables in the if part of a rule and asks the user for their values if needed
bool initializeAllClauseVariables(const conclusion_type &clause, variable_type &variableMap) {
	for (conclusion_type::const_iterator clauseVariable = clause.begin(); clauseVariable != clause.end(); clauseVariable++) {
		if (!variableMap[clauseVariable->first].isInitialized) {
			variableMap[clauseVariable->first].value = getUserInput(variableMap[clauseVariable->first].prompt, variableMap[clauseVariable->first].acceptedValues);
			variableMap[clauseVariable->first].isInitialized = true;
		}

		// If the user's given value doesn't match the rule's requirement, give up on the rule
		if (!equalsIgnoreCase(variableMap[clauseVariable->first].value, clauseVariable->second)) {
			return false;
		}
	}

	// All variables are initialized and match the rule's requirements
	return true;
}

// This method takes a known conclusion and tries to find any other conclusions that can be derived from it
void findConclusions(const string &variable, variable_type &variableMap, const clause_type &clauseVariableList, const conclusion_type &conclusionList, conclusion_type &foundConclusions, int conclusionsFoundCount) {
	for (unsigned int x = 0; x < clauseVariableList.size(); x++) {
		for (unsigned int y = 0; y < clauseVariableList[x].size(); y++) {
            // If the given conclusion is in the if clause of a rule
			if (equalsIgnoreCase(variable, clauseVariableList[x][y].first)) {
			    // Initialize the rest of the if clause for the rule
				bool successfulRule = initializeAllClauseVariables(clauseVariableList[x], variableMap);

                // If all if parts of the rule evaluated to true, execute the then part
				if (successfulRule) {
					variableMap[conclusionList[x].first].value = conclusionList[x].second;
					variableMap[conclusionList[x].first].isInitialized = true;
					foundConclusions.push_back(conclusionList[x]);
				}
			}
		}
	}

    // If any new conclusions were found, see if they allow any more conclusions to be found
	for (unsigned int x = conclusionsFoundCount; x < foundConclusions.size(); x++) {
		// Recursive call to simulate conclusion variable queue
		findConclusions(foundConclusions[x].first, variableMap, clauseVariableList, conclusionList, foundConclusions, foundConclusions.size());
	}
}

// This method is the main access point for starting the forwards chaining process
conclusion_type runForwardsChaining(const string &variable, const string &value) {
	conclusion_type conclusionList;
	variable_type variableMap;
	clause_type clauseVariableList;

	// Filling data structures
	readKnowledgeBase(FORWARDS_KNOWLEDGE_BASE, conclusionList, variableMap, clauseVariableList);

	// Forwards Chaining
	variableMap[variable].value = value;
	variableMap[variable].isInitialized = true;
	conclusion_type foundConclusions;
	findConclusions(variable, variableMap, clauseVariableList, conclusionList, foundConclusions, 0);

	/* Debug output
	cout << "VARIABLES VALUES:" << endl;
	for (map<string, variableInfo>::iterator variable = variableMap.begin(); variable != variableMap.end(); variable++) {
		cout << variable->first << ": " << variable->second.value << endl;
	}
	*/

	return foundConclusions;
}
