// Author: Terry Penner
// Date Created: Sept. 1, 2014
// File name: BackwardsChaining.h
// Purpose: To perform the backwards chaining algorithm
// Usage: See Project1-A04367972.cpp

#ifndef BACKWARDS_CHAINING_HEADER
#define BACKWARDS_CHAINING_HEADER

// The header that includes information for reading the knowledge base file
#include "KnowledgeBase.h"

// The file where the knowledge base is defined
#define BACKWARDS_KNOWLEDGE_BASE "BackwardsKnowledgeBase.txt"

// The main access point for starting the backwards chaining process
string runBackwardsChaining(const string &conclusion);

#endif
