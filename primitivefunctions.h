#ifndef PRIMITIVEFUNCTIONS_H
#define PRIMITIVEFUNCTIONS_H

#include "definitions.h"
#include "expressions.h"

namespace PrimitiveFunctions
{
        sExpression * CAR(sExpression * input);
        sExpression * CDR(sExpression * input);
        sExpression * CONS(sExpression * e1, sExpression * e2);
        sExpression * ATOM(sExpression * input);
        sExpression * EQ(sExpression * e1, sExpression * e2);
        sExpression * ISNULL(sExpression * input);
        sExpression * INT(sExpression * input);
        sExpression * PLUS(sExpression * input);
        sExpression * MINUS(sExpression * input);
        sExpression * TIMES(sExpression * input);
        sExpression * QUOTIENT(sExpression * input);
        sExpression * REMAINDER(sExpression * input);
        sExpression * LESS(sExpression * input);
        sExpression * GREATER(sExpression * input);
        sExpression * QUOTE(sExpression * input);
	#if 0
        sExpression * COND(sExpression * input);
        sExpression * DEFUN(sExpression * input);
	#endif
	extern sExpression * T; //= new sExpression("T");
	extern sExpression * NIL; //= new sExpression("NIL");
};

#endif
