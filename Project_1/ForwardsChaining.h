// Author: Terry Penner
// Date Created: Sept. 1, 2014
// File name: ForwardsChaining.h
// Purpose: To perform the forwards chaining algorithm
// Usage: See Project1-A04367972.cpp

#ifndef FORWARDS_CHAINING_HEADER
#define FORWARDS_CHAINING_HEADER

// The header that includes information for reading the knowledge base file
#include "KnowledgeBase.h"

// The file where the knowledge base is defined
#define FORWARDS_KNOWLEDGE_BASE "ForwardsKnowledgeBase.txt"

// The main access point for starting the forwards chaining process
conclusion_type runForwardsChaining(const string &variable, const string &value);

#endif
