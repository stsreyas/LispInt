#ifndef PARSER_H
#define PARSER_H

#include "definitions.h"

typedef struct specialString
{	
	specialString()
	{
		isValid = false;
		errorCode = -1;		
	}
	bool isValid;
	string s;
	int errorCode;
}str;

class parser
{
public:
	parser();
	~parser();
	
	string parseExpression(string expression);
	string generateExpression();
private:

	string inputString, outputString;
	


};

#endif
