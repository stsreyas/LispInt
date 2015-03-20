#ifndef PARSER_H
#define PARSER_H

#include "definitions.h"
#include "expressions.h"

#define LOG

// errorCodes
// 0 no error
// 1 unexpected token

class ParamPacket
{
public:
	ParamPacket()
	{
		_isList = false;
		_strPtr = 0;
		_errorCode = 0;
		_pointerSeen = false;
	}
	bool _isList;
	bool _pointerSeen;
	int _strPtr;
	string _errorMessage;
	int _errorCode;
};

class Parser
{
public:
	Parser();
	~Parser();
	
	string Parse(string expression);
private:

	string inputString, outputString;
	int * _inputEncoded;
	void generateExpression();
	void traverseAndGenerate(sExpression * parent);
	int checkToken(char ch);
	bool encodeString(string input);
	ParamPacket evaluateExpression();
	ParamPacket evaluate(int strPtr, sExpression *tree, bool listFlag);
	string pruneString(string expression);
	sExpression * expTree;
};

#endif
