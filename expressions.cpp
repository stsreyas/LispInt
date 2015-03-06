#include "expressions.h"

sExpression::sExpression()
{
	this->left = NULL;
	this->right = NULL;
	id = 0;
}

sExpression::sExpression(ExpressionType eType)
{
	this->left = NULL;
	this->right = NULL;
	id = 0;
	type = eType; 
}

sExpression::~sExpression()
{
	
}

bool sExpression::insert(sExpression * leaf)
{
	if(this->left == NULL)
	{	
		this->left = leaf;
		return true;
	}
	else if(this->right == NULL)
	{
		this->right = leaf;
		return true;
	}
	else
		return false;
}
