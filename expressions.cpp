#include "expressions.h"

sExpression::sExpression()
{
	this->left = NULL;
	this->right = NULL;
	id = 0;
	type = ATOMIC;
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

sExpression * sExpression::initLeaf()
{
	this->type = NON_ATOMIC;
	if(this->left == NULL)
	{
		cout<<"\nLEFT\n";
		this->left = new sExpression;
		return this->left;
	}
	else if(this->right == NULL)
	{
		cout<<"\nRIGHT\n";
		this->right = new sExpression;
		return this->right;
	}
	return NULL;
}

void sExpression::setString(string s)
{
	this->s = s;
}
