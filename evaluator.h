#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "definitions.h"
#include "expressions.h"
#include "primitivefunctions.h"

using namespace PrimitiveFunctions;

class aList
{
public:
	aList(){};
	~aList(){};
	std::map<string, string> _aList;
};


class Evaluator
{
public:
	Evaluator();
	~Evaluator();
	sExpression * eval(sExpression * input);

private:

	sExpression * evCond(sExpression * input, aList a);
	sExpression * evaluate(sExpression * input, aList a);
	sExpression * evList(sExpression * input, aList a);
	sExpression * apply(sExpression * f, sExpression * input, aList a);
	void add2DList(sExpression * f);
	//void add2AList(sExpression * p1, sExpression * c1
	aList generateAList(sExpression * argList1, sExpression * argList2, aList inp);	
	sExpression * getFromDList(sExpression * input);
	std::vector<sExpression *> _dList;
	void traverseArgLists(sExpression * l1, sExpression * l2, aList * ret);
};

#endif
