#ifndef DEFINITIONS_H
#define DEFINITIONS_H

using namespace std;

#include <iostream>
#include <stdio.h>
#include <string>

static string TOKENCODE[5] = {"Alphanumeric", "Opening Brace", "Pointer", "Whitespace", "Closing Brace"};

static bool TRANSITION[5][5] = 
	{
		{1, 1, 1, 1, 0}, // For alphanumeric
		{0, 1, 1, 1, 0}, // For opening brace
		{1, 0, 0, 0, 1}, // For pointer
		{1, 1, 0, 0, 1}, // For whitespace
		{1, 1, 0, 0, 1}  // For closing brace
	};

#endif
