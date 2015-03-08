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

class ParamPacket
{
public:
	ParamPacket()
	{
		_isList = false;
		_parent = NULL;
		_strPtr = 0;
		_errorCode = 0;
	}
	ParamPacket(string input, string encoded, sExpression * parent, bool isList)
	{
		_input = input;
		_encoded = encoded;
		_parent = parent;
		_isList = isList;	
	}
	bool _isList;
	int _strPtr;
	sExpression * _parent;
	string _input;
	string _encoded;
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
	string  _skipCode;
	StringPacket parseExpression(string expression, bool listFlag, sExpression * parent, int prevToken);
	//ParamPacket parseExpression(ParamPacket input)
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
