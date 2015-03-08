#ifndef DEFINITIONS_H
#define DEFINITIONS_H

using namespace std;

#include <iostream>
#include <stdio.h>

typedef enum validTokens{INVALID, BRACE_OPEN, BRACE_CLOSED, COMMA, WHITESPACE, POINTER, INTEGER, IDENTIFIER} ValidTokens;

#if 0
class Token
{
public:
	Token();
	~Token();
	
private:

	ValidTokens tokenId;
	int ** transitions;
		

}
#endif
typedef struct Token
{
	ValidTokens tokenId;
	Token()
	{
		tokenId = INVALID;
	}
	
	void CheckToken(char* input, int len)
	{}	 

};

#endif
