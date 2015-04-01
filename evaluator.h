#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "definitions.h"
#include "expressions.h"
#include "primitivefunctions.h"

using namespace PrimitiveFunctions;

class Evaluator
{
public:
	Evaluator();
	~Evaluator();

	sExpression * evaluate(sExpression * input);

private:

	sExpression * evCond(sExpression * input);
	sExpression * evList(sExpression * input);
	sExpression * apply(sExpression * f, sExpression * input);
};

#endif
