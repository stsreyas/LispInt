#include "primitivefunctions.h"

using namespace PrimitiveFunctions;

sExpression * PrimitiveFunctions::T = new sExpression("T");
sExpression * PrimitiveFunctions::NIL = new sExpression("NIL");
sExpression * PrimitiveFunctions::ERR = new sExpression("**Error**");

sExpression * PrimitiveFunctions::CAR(sExpression * input)
{
	if(PrimitiveFunctions::ATOM(input)->getString() == "T")
	{
		cout<<"\nError: Input to CAR is ATOMIC\n";
	}
	return input->getLeft();
}

sExpression * PrimitiveFunctions::CDR(sExpression * input)
{
	if(PrimitiveFunctions::ATOM(input)->getString() == "T")
	{
		cout<<"\nError: Input to CDR is ATOMIC\n";
	}
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

sExpression * PrimitiveFunctions::nEq(sExpression * e1, sExpression * e2)
{	
	if((PrimitiveFunctions::INT(e1)->getString() == "T"))
	{ 
		if(PrimitiveFunctions::INT(e2)->getString() == "T")
		{
			if(e1->getValue() == e2->getValue())
				return PrimitiveFunctions::T;
		}
	}
	else
	{
		if(PrimitiveFunctions::INT(e2)->getString() == "NIL")
		{
			if(e1->getString() == e2->getString())
				return PrimitiveFunctions::T;
		
		}
	}
	return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::EQ(sExpression * e1, sExpression * e2)
{
	if(PrimitiveFunctions::ATOM(e1)->getString() == "T")
	{
		if(PrimitiveFunctions::ATOM(e2)->getString() == "T")
			return nEq(e1, e2);
	}
	else if(EQ(e1->getLeft(), e2->getLeft())->getString() == "T")
	{
		return(EQ(e1->getRight(), e2->getRight()));
	}
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
