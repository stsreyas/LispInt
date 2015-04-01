#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "definitions.h"


typedef enum expType{ATOMIC_NUMERIC, ATOMIC_SYMBOLIC, NON_ATOMIC, UNKNOWN}ExpressionType;

#if 0
class expression
{
public:
	expression(ExpressionType type) 
	{
		_type = type;
	};
	~expression();
	virtual void init() = 0;
	virtual void retreive() = 0;

private:
	ExpressionType _type;
};


class numeric : public expression 
{
public:
	numeric(ExpressionType type) : expression(type) {}; 
	~numeric();
	void init();
	void retreive();
	
private:
	ExpressionType _type;
	string _s;
	int id;
};

class identifier : public expression
{
public:
	

private:



};

class nonAtomic : public expression
{
public:

private:



};

#endif

class sExpression
{
public:
	sExpression();
	sExpression(string s);
	~sExpression();
	void initLeaf(sExpression * child);
	sExpression * initLeaf();
	void setString(string s);
	void setValue(int val);
	sExpression * getLeft();
	sExpression * getRight();
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
