#include "evaluator.h"

Evaluator::Evaluator()
{


}

Evaluator::Evaluator(userDefines *defs)
{
	Evaluator();
	_userDefs = defs;
}

Evaluator::~Evaluator()
{


}

sExpression * Evaluator::eval(sExpression * input)
{
	aList a;
	sExpression * ret = evaluate(input, a);
	return ret;

}

sExpression * Evaluator::returnExpression(string name)
{
        sExpression *obj = _userDefs->returnExisting(name);
	if(obj == NULL)
	{
		std::string::size_type sz;
		int val = std::stoi(name, &sz);
		sExpression * ret = new sExpression(val);
		return ret;	
	}
	return obj;
}
sExpression * Evaluator::evaluate(sExpression * input, aList a)
{
	sExpression * res1 = PrimitiveFunctions::ATOM(input);
	if(res1->getString() == "T")
	{	
		if(a.findElem(input->getString()))
		{
			sExpression * ret = returnExpression(a._aList[input->getString()]);
			return ret;
		}
		else
		{
			// check in a list else return as is
			return input;
		}
	}
	else
	{
		sExpression * res2 = PrimitiveFunctions::ATOM(input->getLeft()); 
		if(res2->getString() == "T")
		{	// Some function application
			sExpression * res3 = input->getLeft();
			if(res3->getString() == "QUOTE")
			{
				return input->getRight()->getLeft();		
			}
			else if(res3->getString() == "COND")
			{
				return evCond(input->getRight(), a);
			}
			else if(res3->getString() == "DEFUN")
			{
				//add to dlist;
				add2DList(input->getRight());
			}
			else
			{
				sExpression * f = input->getLeft();
				sExpression * inp = input->getRight();
				sExpression * evInp = evList(inp, a);
				if(evInp->getString() == "**Error**")
					return evInp;
				return apply(f, evInp, a);
			}
		}
		else
		{
			cout<<"\nError: Improper statement 1\n";	
			return PrimitiveFunctions::ERR;
		}
	}
//	cout<<"\nError: Improper statement 2\n";	
	return PrimitiveFunctions::NIL;
}

aList Evaluator::generateAList(sExpression * argList1, sExpression * argList2, aList inp)
{
	aList retList = inp;
	bool status = traverseArgLists(argList1, argList2, &retList);	
	if(!status)
		retList.errCode = 1;

	return retList;
}

bool Evaluator::traverseArgLists(sExpression * l1, sExpression *l2, aList * ret)
{
	if(PrimitiveFunctions::ISNULL(l1->getRight())->getString() == "T")
	{
		if(PrimitiveFunctions::ISNULL(l2->getRight())->getString() == "T")
		{ // correct number of arguments
			string p1 = l1->getLeft()->getString();
			string p2 = l2->getLeft()->getString();
			ret->_aList[p1] = p2;
			return true;
		}
		else
		{ // num arguments mismatch 
			cout<<"\nError: Too many arguments\n";
			return false;
		}
	}
	else if(PrimitiveFunctions::ISNULL(l2->getRight())->getString() == "T")
	{
		
		cout<<"\nError: Too few arguments\n";
		return false;
	}
	
	string p1 = l1->getLeft()->getString();
	string p2 = l2->getLeft()->getString();
	ret->_aList[p1] = p2;
	bool status = traverseArgLists(l1->getRight(), l2->getRight(), ret);
	return status;
	
}

sExpression * Evaluator::apply(sExpression * f, sExpression * input, aList a)
{
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
		else if(f->getString() == "INT")
			return PrimitiveFunctions::INT(input->getLeft());
		else if(f->getString() == "PLUS")
			return PrimitiveFunctions::PLUS(input);
		else if(f->getString() == "MINUS")
			return PrimitiveFunctions::MINUS(input);
		else if(f->getString() == "TIMES")
			return PrimitiveFunctions::TIMES(input);
		else if(f->getString() == "QUOTIENT")
			return PrimitiveFunctions::QUOTIENT(input);
		else if(f->getString() == "REMAINDER")
			return PrimitiveFunctions::REMAINDER(input);
		else if(f->getString() == "LESS")
			return PrimitiveFunctions::LESS(input);
		else if(f->getString() == "GREATER")
			return PrimitiveFunctions::GREATER(input);
		else if(f->getString() == "EQ")
			return PrimitiveFunctions::EQ(input->getLeft(), input->getRight()->getLeft());
		else 
		{	// User defined functions
			sExpression * fPtr = getFromDList(f);
			if(fPtr == NULL)
			{
				cout<<"\nError: Undefined function name\n";
				return PrimitiveFunctions::ERR;
			}
			// check for undefined functions
			// generate a-list here using car of fPtr and input (args)
			aList a1;
			a1 = generateAList(fPtr->getLeft(), input, a1);
			if((a1.errCode) == 1)
				return PrimitiveFunctions::ERR;
			sExpression * ret = evaluate(fPtr->getRight()->getLeft(), a1);
			return ret;
		}
	}
	
	cout<<"\nError: Improper Statement 3\n";
	return PrimitiveFunctions::ERR;
//	return PrimitiveFunctions::NIL; // this is an error case
}


sExpression * Evaluator::evCond(sExpression * input, aList a)
{
	sExpression * res1 = PrimitiveFunctions::ISNULL(input);
	if(res1->getString() == "T")
	{
		cout<<"\nError: Improper conditional\n";
		return PrimitiveFunctions::ERR; //this is an error case
	}
	else
	{
		sExpression * caar = input->getLeft()->getLeft();	
		sExpression * bi = evaluate(caar, a);
		if(bi->getString() == "T")
		{
			sExpression * cadar = input->getLeft()->getRight()->getLeft();
			sExpression * ei = evaluate(cadar, a);
			return ei;
		}
		else
		{
			return evCond(input->getRight(), a);
		}
	}
}


sExpression * Evaluator::evList(sExpression * input, aList a)
{
	sExpression * res1 = PrimitiveFunctions::ISNULL(input);
	if(res1->getString() == "T")
	{// this is an error case
	//	cout<<"\nError: Irregular List Structure\n";
		return PrimitiveFunctions::NIL;
	}
	else
	{
		sExpression * par1 = evaluate(input->getLeft(), a);
		if(par1->getString() == "**Error**")
			return par1;
		sExpression * par2 = evList(input->getRight(), a);
		if(par2->getString() == "**Error**")
			return par2;
		sExpression * ret = PrimitiveFunctions::CONS(par1, par2);
		return ret;
	}
}

sExpression * Evaluator::getFromDList(sExpression * input)
{
	
        std::vector<sExpression *>::size_type iter;
	string name = input->getString();
        //check primitives
        for(iter = 0; iter != _dList.size(); iter++)
        {
                string str = _dList.at(iter)->getLeft()->getString();
                if(str == name)
                {
                        return _dList.at(iter)->getRight();
                }
        }
        return  PrimitiveFunctions::NIL;
}

void Evaluator::add2DList(sExpression * f)
{
	_dList.push_back(f);
}
