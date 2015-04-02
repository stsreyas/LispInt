#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "definitions.h"
#include "expressions.h"
#include "primitivefunctions.h"
#include "userdefines.h"

using namespace PrimitiveFunctions;

class aList
{
public:
	aList(){errCode = 0;};
	~aList(){};
	bool findElem(string name)
	{
		std::map<string, string>::iterator it;
		it = _aList.find(name);
		if(it != _aList.end())
			return true;
		else
			return false;
	};
	std::map<string, string> _aList;
	int errCode;
};


class Evaluator
{
public:
	Evaluator();
	Evaluator(userDefines * defs);
	~Evaluator();
	sExpression * eval(sExpression * input);

private:

	sExpression * evCond(sExpression * input, aList a);
	sExpression * evaluate(sExpression * input, aList a);
	sExpression * evList(sExpression * input, aList a);
	sExpression * apply(sExpression * f, sExpression * input, aList a);
	void add2DList(sExpression * f);
	aList generateAList(sExpression * argList1, sExpression * argList2, aList inp);	
	sExpression * getFromDList(sExpression * input);
	std::vector<sExpression *> _dList;
	bool traverseArgLists(sExpression * l1, sExpression * l2, aList * ret);
	sExpression * returnExpression(string name);
	userDefines *_userDefs;
};	

#endif
