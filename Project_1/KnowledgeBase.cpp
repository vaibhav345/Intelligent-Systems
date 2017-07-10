// Author: Terry Penner
// Date Created: Sept. 1, 2014
// File name: KnowledgeBase.cpp
// Purpose: To parse the given knowledge base file
// Usage: See Project1-A04367972.cpp

#include "KnowledgeBase.h"

// Function Prototypes
// ****************************************************************************
string readVariables(fstream &knowledgeBase, variable_type &variableMap);
string readRules(fstream &knowledgeBase, clause_type &clauseVariableList, conclusion_type &conclusionList);

// Main functions
// ****************************************************************************
void readKnowledgeBase(const string &knowledgeBaseFile, conclusion_type &conclusionList, variable_type &variableMap, clause_type &clauseVariableList) {
	fstream knowledgeBase;
	knowledgeBase.open(knowledgeBaseFile.c_str());
	if (knowledgeBase.is_open()) {
		string line;
		getline(knowledgeBase, line);
		if (line.find(IGNORE_FILE_LINE) != string::npos) {
			line = readVariables(knowledgeBase, variableMap);
		}
		if (line.find(IGNORE_FILE_LINE) != string::npos) {
			line = readRules(knowledgeBase, clauseVariableList, conclusionList);
		}
	}
	knowledgeBase.close();
}

string readVariables(fstream &knowledgeBase, variable_type &variableMap) {
	string line;
	while (getline(knowledgeBase, line) && line.find(IGNORE_FILE_LINE) == string::npos) {
		vector<string> components = split(line, ';');

		if (components.size() == 3) {
			trim(components);

			variableInfo info;
			info.isInitialized = false;
			info.acceptedValues = split(components[1], ',');
			trim(info.acceptedValues);
			info.prompt = components[2];

			variableMap[components[0]] = info;
		}
	}
	return line;
}

string readRules(fstream &knowledgeBase, clause_type &clauseVariableList, conclusion_type &conclusionList) {
	string line;
	conclusion_type clause;
	while (getline(knowledgeBase, line) && line.find(IGNORE_FILE_LINE) == string::npos) {
		vector<string> components = split(line, '=');
		trim(components);
		if (components.size() == 2 && components[0][0] == '-') {
			clauseVariableList.push_back(clause);
			clause.clear();

			pair<string, string> conclusionPair(components[0].substr(1), components[1]);
			conclusionList.push_back(conclusionPair);
		}
		else if (components.size() == 2) {
			pair<string, string> clausePair(components[0], components[1]);
			clause.push_back(clausePair);
		}
	}
	return line;
}

// Support functions
// ****************************************************************************
void trimRight(string &text, const string &whiteSpace) {
	int lastPosition = text.find_last_not_of(whiteSpace);
	text.erase(lastPosition + 1);
}

void trimLeft(string &text, const string &whiteSpace) {
	int firstPosition = text.find_first_not_of(whiteSpace);
	text.erase(0, firstPosition);
}

void trim(string &text) {
	const string whiteSpace(" \f\n\r\t\v");
	trimRight(text, whiteSpace);
	trimLeft(text, whiteSpace);
}

void trim(vector<string> &textList) {
	for (vector<string>::iterator text = textList.begin(); text != textList.end(); text++) {
		trim(*text);
	}
}

vector<string> &split(const string &text, char deliminator, vector<string> &subSections) {
    stringstream textStream(text);
    string item;
    while (getline(textStream, item, deliminator)) {
        subSections.push_back(item);
    }
    return subSections;
}

vector<string> split(const string &text, char deliminator) {
    vector<string> subSections;
    split(text, deliminator, subSections);
    return subSections;
}

bool equalsIgnoreCase(const string &string1, const string &string2) {
	if (string1.size() != string2.size()) {
		return false;
	}
	for (unsigned int x = 0; x < string1.size(); x++) {
		if (tolower(string1[x]) != tolower(string2[x])) {
			return false;
		}
	}
	return true;
}
