#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "definitions.h"


typedef enum expType{ATOMIC, NON_ATOMIC}ExpressionType;

class sExpression
{
public:
	sExpression();
	~sExpression();
	sExpression * initLeaf();
	void setString(string s);
	sExpression * getLeft();
	sExpression * getRight();
	ExpressionType getType();
	string getString();

private:
	sExpression * left;
	sExpression * right;
	ExpressionType type;
	string s;
	int id;
};


#endif
