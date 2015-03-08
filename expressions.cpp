#include "expressions.h"

sExpression::sExpression()
{
	this->left = NULL;
	this->right = NULL;
	id = 0;
	type = ATOMIC;
}

sExpression::~sExpression()
{
	if(this->left != NULL)
		delete this->left;
	if(this->right != NULL)
		delete this->right;
}

sExpression * sExpression::initLeaf()
{
	this->type = NON_ATOMIC;
	if(this->left == NULL)
	{
		this->left = new sExpression;
		return this->left;
	}
	else if(this->right == NULL)
	{
		this->right = new sExpression;
		return this->right;
	}
	return NULL;
}

void sExpression::setString(string s)
{
	this->s = ATOMIC;
	this->s = s;
}

sExpression * sExpression::getLeft()
{
	if(this->left != NULL)
		return this->left;
	return NULL;
}

sExpression * sExpression::getRight()
{
	if(this->right != NULL)
		return this->right;
	return NULL;
}

ExpressionType sExpression::getType()
{
	return this->type;
}

string sExpression::getString()
{
	return this->s;
}
