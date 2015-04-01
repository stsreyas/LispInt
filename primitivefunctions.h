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
	#if 0
        sExpression * EQ(sExpression * e1, sExpression * e2);
        sExpression * ISNULL(sExpression * input);
        sExpression * INT(sExpression * input);
        sExpression * PLUS(sExpression * e1, sExpression * e2);
        sExpression * MINUS(sExpression * e1, sExpression * e2);
        sExpression * TIMES(sExpression * e1, sExpression * e2);
        sExpression * QUOTIENT(sExpression * e1, sExpression * e2);
        sExpression * REMAINDER(sExpression * e1, sExpression * e2);
        sExpression * LESS(sExpression * e1, sExpression * e2);
        sExpression * GREATER(sExpression * e1, sExpression * e2);
        sExpression * COND(sExpression * input);
        sExpression * QUOTE(sExpression * input);
        sExpression * DEFUN(sExpression * input);
	#endif
	extern sExpression * T; //= new sExpression("T");
	extern sExpression * NIL; //= new sExpression("NIL");
};

#endif
