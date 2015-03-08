#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "definitions.h"

#if 0
struct node
{
	node()
	{
		value = 0;
		left = NULL;
		right = NULL;
	}
	int value;
	node * left;
	node * right;
}
#endif

typedef enum expType{ATOMIC, NON_ATOMIC}ExpressionType;

class sExpression
{
public:
	sExpression();
	sExpression(ExpressionType eType);
	~sExpression();
	//bool insert(sExpression * leaf);
	sExpression * initLeaf();
	void setString(string s);
	//void setExpressionType(ExpressionType eType);
	//void traverse();
	//void destroy();	
	sExpression * left;
	sExpression * right;
	ExpressionType type;
	string s;
	int id;
};


#endif
