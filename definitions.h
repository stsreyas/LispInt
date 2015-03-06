#ifndef DEFINITIONS_H
#define DEFINITIONS_H

using namespace std;

#include <iostream>

typedef enum validTokens{INVALID, BRACE_OPEN, BRACE_CLOSED, COMMA, WHITESPACE, POINTER, INTEGER, IDENTIFIER} ValidTokens;

class Token
{
public:
	Token();
	~Token();
	
private:

	ValidTokens tokenId;
	int ** transitions;
		

}

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
