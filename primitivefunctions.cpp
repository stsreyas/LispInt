#include "primitivefunctions.h"

using namespace PrimitiveFunctions;

sExpression * PrimitiveFunctions::T = new sExpression("T");
sExpression * PrimitiveFunctions::NIL = new sExpression("NIL");

sExpression * PrimitiveFunctions::CAR(sExpression * input)
{
	cout<<"\nInside car\n";
	return input->getLeft();
}

sExpression * PrimitiveFunctions::CDR(sExpression * input)
{
	cout<<"\nInside cdr\n";
	return input->getRight();
}

sExpression * PrimitiveFunctions::CONS(sExpression * e1, sExpression * e2)
{
	cout<<"\nInside cons\n";
	sExpression * parent = new sExpression;
	parent->initLeaf(e1);
	parent->initLeaf(e2);
	return parent;
}


sExpression * PrimitiveFunctions::ATOM(sExpression * input)
{
	cout<<"\nInside atom\n";
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
	cout<<"\nInside eq\n";
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
	cout<<"\nInside null\n";
	if((input->getType() != NON_ATOMIC) && (input->getString() == "NIL"))
		return PrimitiveFunctions::T;
	else
		return PrimitiveFunctions::NIL;
}

sExpression * PrimitiveFunctions::INT(sExpression * input)
{
	cout<<"\nInside int\n";
	if(input->getType() == ATOMIC_NUMERIC)
		return PrimitiveFunctions::T;
	else
		return PrimitiveFunctions::NIL;	
}

sExpression * PrimitiveFunctions::PLUS(sExpression * input)
{
	cout<<"\nInside plus\n";
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
	cout<<"\nInside minus\n";
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
	cout<<"\nInside times\n";
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
	cout<<"\nInside quotient\n";
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
	cout<<"\nInside remainder\n";
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
	cout<<"\nInside less\n";
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
	cout<<"\nInside greater\n";
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
