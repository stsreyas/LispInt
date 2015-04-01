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
