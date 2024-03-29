#include "expressions.h"

sExpression::sExpression()
{
	this->left = NULL;
	this->right = NULL;
	val = 0;
	type = UNKNOWN;
}

sExpression::sExpression(string s)
{
	sExpression();
	this->type = ATOMIC_SYMBOLIC;
	this->s = s;
}

sExpression::sExpression(int val)
{
	sExpression();
	this->type = ATOMIC_NUMERIC;
	this->val = val;
	this->s = std::to_string(val);
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

void sExpression::initLeaf(sExpression * child)
{
	this->type = NON_ATOMIC;
	if(this->left == NULL)
	{
		this->left = child;
		return;
	}
	else if(this->right == NULL)
	{
		this->right = child;
		return;
	}
}
void sExpression::setString(string s)
{
	this->type = ATOMIC_SYMBOLIC;
	this->s = s;
}

void sExpression::setValue(int val)
{
	this->type = ATOMIC_NUMERIC;
	this->val = val;
	this->s = std::to_string(val);
} 

int sExpression::getValue()
{
	return this->val;
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
