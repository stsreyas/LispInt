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

typedef enum expType{ATOMIC_NUMBER, ATOMIC_ID, NON_ATOMIC}ExpressionType;

class sExpression
{
public:
	sExpression();
	sExpression(ExpressionType eType);
	~sExpression();
	bool insert(sExpression * leaf);
	//void insert(node * head);
	//void traverse();
	//void destroy();	
	

private:
	ExpressionType type;
	string s;
	int id;
	sExpression * left;
	sExpression * right;
};


#endif
