#include "evaluator.h"

Evaluator::Evaluator()
{


}


Evaluator::~Evaluator()
{


}


sExpression * Evaluator::evaluate(sExpression * input)
{
	cout<<"\n inside evaluate"<<endl;
	sExpression * res1 = PrimitiveFunctions::ATOM(input);
	if(res1->getString() == "T")
	{	
		cout<<"\n atom :" << input->getString()<<endl;
		return input;
	}
	else
	{
		sExpression * res2 = PrimitiveFunctions::ATOM(input->getLeft()); 
		if(res2->getString() == "T")
		{	// Some function application
			sExpression * res3 = input->getLeft();
			if(res3->getString() == "QUOTE")
			{
				cout<<"\n quote: R -> L"<<endl;
				return input->getRight()->getLeft();		
			}
			else
			{
				sExpression * f = input->getLeft();
				cout<<"\n f: L"<<endl;
				sExpression * inp = input->getRight();
				cout<<"\n evInp: R"<<endl;
				sExpression * evInp = evList(inp);
				return apply(f, evInp);
			}
		}
		else
			return PrimitiveFunctions::NIL;
	}
	return PrimitiveFunctions::NIL;		
}

sExpression * Evaluator::apply(sExpression * f, sExpression * input)
{
	cout<<"\n inside apply"<<endl;
	if(PrimitiveFunctions::ATOM(f)->getString() == "T")
	{
		if(f->getString() == "CAR")
			return input->getLeft()->getLeft();
		else if(f->getString() == "CDR")
			return input->getLeft()->getRight();
		else if(f->getString() == "CONS")
			// cdr or cadr??
			return PrimitiveFunctions::CONS(input->getLeft(), input->getRight()->getLeft());
		else if(f->getString() == "ATOM")
			return PrimitiveFunctions::ATOM(input->getLeft());
		else if(f->getString() == "NULL")
			return PrimitiveFunctions::ISNULL(input->getLeft());
		else
			return PrimitiveFunctions::NIL;
	}
	return PrimitiveFunctions::NIL;
	
	#if 0
	else if((res3->getString() == "CAR") || (res3->getString() == "CDR") 
		|| (res3->getString() == "ATOM") || (res3->getString() == "INT")
		|| (res3->getString() == "NULL") || (res3->getString() == "CONS")
	        || (res3->getString() == "PLUS") 
		|| (res3->getString() == "MINUS") || (res3->getString() == "TIMES")
		|| (res3->getString() == "QUOTIENT") || (res3->getString() == "REMAINDER")
		|| (res3->getString() == "LESS") || (res3->getString() == "GREATER"))
	{
		sExpression * par1 = evaluate(input->getRight()->getLeft());
		if(res3->getString() == "CAR")
			return PrimitiveFunctions::CAR(par1);
		else if(res3->getString() == "CDR")
			return PrimitiveFunctions::CDR(par1);
		else if(res3->getString() == "ATOM")
			return PrimitiveFunctions::ATOM(par1);
		else if(res3->getString() == "INT")
			return PrimitiveFunctions::INT(par1);
		else if(res3->getString() == "NULL")
			return PrimitiveFunctions::ISNULL(par1);
		else if(res3->getString() == "PLUS")
			return PrimitiveFunctions::PLUS(par1);
		else if(res3->getString() == "MINUS")
			return PrimitiveFunctions::MINUS(par1);
		else if(res3->getString() == "TIMES")
			return PrimitiveFunctions::TIMES(par1);
		else if(res3->getString() == "CONS")
			return PrimitiveFunctions::CONS(par1);
		else if(res3->getString() == "QUOTIENT")
			return PrimitiveFunctions::QUOTIENT(par1);
		else if(res3->getString() == "REMAINDER")
			return PrimitiveFunctions::REMAINDER(par1);
		else if(res3->getString() == "LESS")
			return PrimitiveFunctions::LESS(par1);
		else if(res3->getString() == "GREATER")
			return PrimitiveFunctions::GREATER(par1);
	}
	#endif
}


sExpression * Evaluator::evCond(sExpression * input)
{


}


sExpression * Evaluator::evList(sExpression * input)
{
	cout<<"\n inside evlist"<<endl;
	sExpression * res1 = PrimitiveFunctions::ISNULL(input);
	if(res1->getString() == "T")
	{
		cout<<"\n atom:"<<input->getString()<<endl;
		return PrimitiveFunctions::NIL;
	}
	else
	{
		cout<<"\n par1: L"<<endl;
		sExpression * par1 = evaluate(input->getLeft());
		cout<<"\n par2: R"<<endl;
		sExpression * par2 = evList(input->getRight());
		sExpression * ret = PrimitiveFunctions::CONS(par1, par2);
		return ret;
	}
}
