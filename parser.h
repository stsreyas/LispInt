#ifndef PARSER_H
#define PARSER_H

#include "definitions.h"
#include "expressions.h"

#define LOG

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

typedef struct paramPacket
{
	paramPacket()
	{
		isList = false;
		prevToken = -1;
		parent = NULL;
	}
	bool isList;
	int prevToken;
	sExpression * parent;
	string input;
}ParamPacket;

class Parser
{
public:
	Parser();
	~Parser();
	
	string Parse(string expression);
private:

	string inputString, outputString;
	StringPacket parseExpression(string expression, bool listFlag, sExpression * parent, int prevToken);
	//ParamPacket parseExpression(ParamPacket input)
	void generateExpression();
	void traverseAndGenerate(sExpression * parent);
	int checkToken(char ch);
	string pruneString(string expression);
	sExpression * expTree;
};

#endif
