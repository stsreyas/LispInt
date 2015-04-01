#ifndef PARSER_H
#define PARSER_H

#include "definitions.h"
#include "expressions.h"
#include "userdefines.h"
#include "primitives.h"

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
		_errorMessage = "Error: ";
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
	Parser(userDefines * uPtr, Primitives * pPtr);
	~Parser();
	
	string Parse(string expression);
	sExpression * getParsedExpression();
	void traverseAndGenerate(sExpression * parent);
	string getOutputString();
private:

	string inputString, outputString;
	int * _inputEncoded;
	void generateExpression();
	int checkToken(char ch);
	bool encodeString(string input);
	ParamPacket evaluateExpression();
	ParamPacket evaluate(int strPtr, sExpression *tree, bool listFlag);
	ParamPacket checkSyntax();
	string pruneString(string expression);
	string pruneCharacters(string input, string str2Find, string strReplace);
	sExpression * returnExpression(string name);
	sExpression * expTree;
	userDefines * _userDefs;
	Primitives * _primitives;
};

#endif
