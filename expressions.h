#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "definitions.h"


typedef enum expType{ATOMIC_NUMERIC, ATOMIC_SYMBOLIC, NON_ATOMIC, UNKNOWN}ExpressionType;

class sExpression
{
public:
	sExpression();
	sExpression(string s);
	sExpression(int val);
	~sExpression();
	void initLeaf(sExpression * child);
	sExpression * initLeaf();
	void setString(string s);
	void setValue(int val);
	sExpression * getLeft();
	sExpression * getRight();
	int getValue();
	ExpressionType getType();
	string getString();

private:
	sExpression * left;
	sExpression * right;
	ExpressionType type;
	string s;
	int val;
};


#endif
