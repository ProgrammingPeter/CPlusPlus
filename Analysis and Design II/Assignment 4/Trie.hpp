/************************************************************************
 Title         : Trie.hpp
 Author        : Peter Kamaris
 Created on    : May 2 2013
 Description   : Program is designed to create a spell check Dictionary of words
 Purpose       : Assignment4
 Build with    : g++ Trie.hpp
 *************************************************************************/
#ifndef _TRIE_H_
#define _TRIE_H_

#include <string>
#include <iostream> //Not sure if I need to comment this but yeah the same comments are included in main
#include <vector>

using namespace std;

// --------------------------------------------------------------------------
// This is the ADT for an in-memory dictionary implemented as a trie. For
// more on a trie, look at: http://en.wikipedia.org/wiki/Trie or others.
// This file represents the minimum set of functions which should be
// implemented in a subclass.
// --------------------------------------------------------------------------
class Trie {
public:
	// This function opens the file named by the argument. This file is in
	// Unix format with one dictionary entry per line. It must return true
	// when the file has been read into memory; false otherwise.
	virtual bool           addDictionary (string filename) = 0;

	// This function adds a word (the argument) to the dictionary. This
	// must also be written to the dictionary file read in the
	// "addDictionary" function, assuming it has been called. Returns true
	// when the word has been added to the dictionary; false otherwise.
	virtual Trie&           operator+(const string & word) = 0;

	// This function returns the count of the words starting with the
	// prefix (passed as the argument). In the case of sae-sorted.dic and
	// the prefix "this", the function should return 5. If no dictionary
	// entries start with the prefix, this function should return 0.
	virtual int            count (string prefix) = 0;

	// Overloaded version of the above function
	virtual int            count (char * prefix) = 0;

	// This function provides alternative spellings to the prefix (passed
	// as the argument). If no prefix exists in the data, this function
	// removes the rightmost character and re-attempts this function. The
	// return value of the the empty string is implementation-dependent.
	virtual vector<string> alternatives (string prefix) = 0;

	// Overloaded version of the above function
	virtual vector<string> alternatives (char * prefix) = 0;
};


#endif
