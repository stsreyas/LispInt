#ifndef DEFINITIONS_H
#define DEFINITIONS_H

using namespace std;

#include <iostream>
#include <stdio.h>
#include <string>
#include <locale>
#include <algorithm>
#include <map>
static string TOKENCODE[7] = {"Numeric", "Alphabet", "Arithmetic Operator",
				 "Opening Brace", "Pointer", "Whitespace", "Closing Brace"};

// each element denotes the transition between string character codes
// TRANSITION[i][j] = 0 => j cannot precede i (ji is an invalid transition)
// TRANSITION[i][j] = 1 => j can precede i (ji is a valid transition)

static bool TRANSITION[7][7] = 
	{
		{1, 1, 1, 1, 1, 1, 0}, // For numbers
		{1, 1, 0, 1, 1, 1, 0}, // For alphabets
		{0, 0, 0, 1, 1, 1, 0}, // For +,- etc
		{0, 0, 0, 1, 1, 1, 0}, // For opening brace
		{1, 1, 0, 0, 0, 0, 1}, // For pointer
		{1, 1, 0, 0, 0, 0, 1}, // For whitespace
		{1, 1, 0, 1, 0, 0, 1}  // For closing brace
	};

#endif
