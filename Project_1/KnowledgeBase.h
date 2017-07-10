// Author: Terry Penner
// Date Created: Sept. 1, 2014
// File name: KnowledgeBase.h
// Purpose: To parse the given knowledge base file
// Usage: See Project1-A04367972.cpp

#ifndef KNOWLEDGE_BASE_HEADER
#define KNOWLEDGE_BASE_HEADER

#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <utility>

#define IGNORE_FILE_LINE "***"

using namespace std;

// Custom types
// ****************************************************************************
typedef struct {
	bool isInitialized;
	string value;
	string prompt;
	vector<string> acceptedValues;
} variableInfo;
typedef vector<vector<pair<string, string> > > clause_type;
typedef vector<pair<string, string> > conclusion_type;
typedef map<string, variableInfo> variable_type;

// Main functions
// ****************************************************************************
void readKnowledgeBase(const string &knowledgeBaseFile, conclusion_type &conclusionList, variable_type &variableMap, clause_type &clauseVariableList);

// Support functions
// ****************************************************************************
void trim(string &text);
void trim(vector<string> &textList);
vector<string> split(const string &text, char deliminator);
bool equalsIgnoreCase(const string &string1, const string &string2);
string getUserInput(string prompt, const vector<string> &acceptedValues);

#endif
