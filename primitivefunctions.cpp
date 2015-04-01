#include "primitivefunctions.h"

using namespace PrimitiveFunctions;

sExpression * PrimitiveFunctions::T = new sExpression("T");
sExpression * PrimitiveFunctions::NIL = new sExpression("NIL");

sExpression * PrimitiveFunctions::CAR(sExpression * input)
{
	return input->getLeft();
}

sExpression * PrimitiveFunctions::CDR(sExpression * input)
{
	return input->getRight();
}

sExpression * PrimitiveFunctions::CONS(sExpression * e1, sExpression * e2)
{
	sExpression * parent = new sExpression;
	parent->initLeaf(e1);
	parent->initLeaf(e2);
	return parent;
}


sExpression * PrimitiveFunctions::ATOM(sExpression * input)
{
	if(input->getType() != NON_ATOMIC)
		return PrimitiveFunctions::T;
	else
		return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::EQ(sExpression * e1, sExpression * e2)
{
	
	return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::ISNULL(sExpression * input)
{
	if((input->getType() != NON_ATOMIC) && (input->getString() == "NIL"))
		return PrimitiveFunctions::T;
	else
		return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::INT(sExpression * input)
{
	if(input->getType() == ATOMIC_NUMERIC)
		return PrimitiveFunctions::T;
	else
		return PrimitiveFunctions::NIL;	
}

sExpression * PrimitiveFunctions::PLUS(sExpression * input)
{
	sExpression * e1 = input->getLeft();
	sExpression * e2 = input->getRight()->getLeft();
	if((e1->getType() == ATOMIC_NUMERIC) && (e2->getType() == ATOMIC_NUMERIC))
	{
		sExpression * result = new sExpression(e1->getValue() + e2->getValue());
		return result;
	}
	else
		return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::MINUS(sExpression * input)
{
	sExpression * e1 = input->getLeft();
	sExpression * e2 = input->getRight()->getLeft();
	if((e1->getType() == ATOMIC_NUMERIC) && (e2->getType() == ATOMIC_NUMERIC))
	{
		sExpression * result = new sExpression(e1->getValue() - e2->getValue());
		return result;
	}
	else
		return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::TIMES(sExpression * input)
{
	sExpression * e1 = input->getLeft();
	sExpression * e2 = input->getRight()->getLeft();
	if((e1->getType() == ATOMIC_NUMERIC) && (e2->getType() == ATOMIC_NUMERIC))
	{
		sExpression * result = new sExpression(e1->getValue() * e2->getValue());
		return result;
	}
	else
		return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::QUOTIENT(sExpression * input)
{
	sExpression * e1 = input->getLeft();
	sExpression * e2 = input->getRight()->getLeft();
	if((e1->getType() == ATOMIC_NUMERIC) && (e2->getType() == ATOMIC_NUMERIC))
	{
		sExpression * result = new sExpression(e1->getValue() / e2->getValue());
		return result;
	}
	else
		return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::REMAINDER(sExpression * input)
{
	sExpression * e1 = input->getLeft();
	sExpression * e2 = input->getRight()->getLeft();
	if((e1->getType() == ATOMIC_NUMERIC) && (e2->getType() == ATOMIC_NUMERIC))
	{
		sExpression * result = new sExpression(e1->getValue() % e2->getValue());
		return result;
	}
	else
		return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::LESS(sExpression * input)
{
	sExpression * e1 = input->getLeft();
	sExpression * e2 = input->getRight()->getLeft();
	if((e1->getType() == ATOMIC_NUMERIC) && (e2->getType() == ATOMIC_NUMERIC))
	{
		if(e1->getValue() < e2->getValue())
			return PrimitiveFunctions::T;
	}
	return PrimitiveFunctions::NIL; // Need to return some error if non atomic are used
}

sExpression * PrimitiveFunctions::GREATER(sExpression * input)
{
	sExpression * e1 = input->getLeft();
	sExpression * e2 = input->getRight()->getLeft();
	if((e1->getType() == ATOMIC_NUMERIC) && (e2->getType() == ATOMIC_NUMERIC))
	{
		if(e1->getValue() > e2->getValue())
			return PrimitiveFunctions::T;
	}
	return PrimitiveFunctions::NIL; // Need to return some error if non atomic are used
}

sExpression * PrimitiveFunctions::QUOTE(sExpression * input)
{
	if(input->getType() == NON_ATOMIC)
		return input->getRight();
	return PrimitiveFunctions::NIL;
}
