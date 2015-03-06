#ifndef PARSER_H
#define PARSER_H

#include "definitions.h"

// errorCodes
// 0 no error
// 1 unexpected token

typedef struct stringPacket
{	
	#if 1
	stringPacket()
	{
		isValid = false;
		errorCode = 0;		
		offset = 0;
	}
	#endif
	bool isValid;
	string s;
	int errorCode;
	int offset;
}StringPacket;

class Parser
{
public:
	Parser();
	~Parser();
	
	string Parse(string expression);
private:

	string inputString, outputString;
	StringPacket parseExpression(string expression, bool listFlag);
	string generateExpression();
	int checkToken(char ch);
	string pruneString(string expression);
};

#endif
