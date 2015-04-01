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
        sExpression *obj = _userDefs->returnObject(name);
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
	cout<<"\n inside evaluate"<<endl;
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
			cout<<"\n atom :" << input->getString()<<endl;
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
				cout<<"\n quote: R -> L"<<endl;
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
				cout<<"\n f: L"<<endl;
				sExpression * inp = input->getRight();
				cout<<"\n evInp: R"<<endl;
				sExpression * evInp = evList(inp, a);
				return apply(f, evInp, a);
			}
		}
		else
			return PrimitiveFunctions::NIL;
	}
	return PrimitiveFunctions::NIL;		
}

aList Evaluator::generateAList(sExpression * argList1, sExpression * argList2, aList inp)
{
	aList retList = inp;
	traverseArgLists(argList1, argList2, &retList);	
	cout<<"\n A List generated\n";
	return retList;
}

void Evaluator::traverseArgLists(sExpression * l1, sExpression *l2, aList * ret)
{
	if(PrimitiveFunctions::ISNULL(l1->getRight())->getString() == "T")
	{
		if(PrimitiveFunctions::ISNULL(l2->getRight())->getString() == "T")
		{ // correct number of arguments
			string p1 = l1->getLeft()->getString();
			string p2 = l2->getLeft()->getString();
			ret->_aList[p1] = p2;
			cout<<endl<<p1<<"="<<ret->_aList[p1]<<endl;
			return;
		}
		else
		{ // num arguments mismatch 
			cout<<endl<<"Argument mismatch\n";
		}
	}
	
	string p1 = l1->getLeft()->getString();
	string p2 = l2->getLeft()->getString();
	ret->_aList[p1] = p2;
	cout<<endl<<p1<<"="<<ret->_aList[p1]<<endl;
	traverseArgLists(l1->getRight(), l2->getRight(), ret);
}

sExpression * Evaluator::apply(sExpression * f, sExpression * input, aList a)
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
		{	// User defined functions
			sExpression * fPtr = getFromDList(f);
			// check for undefined functions
			// generate a-list here using car of fPtr and input (args)
			aList a1;
			a1 = generateAList(fPtr->getLeft(), input, a1);
			sExpression * ret = evaluate(fPtr->getRight()->getLeft(), a1);
			return ret;
		}
	}
	return PrimitiveFunctions::NIL; // this is an error case
}


sExpression * Evaluator::evCond(sExpression * input, aList a)
{
	sExpression * res1 = PrimitiveFunctions::ISNULL(input);
	if(res1->getString() == "T")
		return PrimitiveFunctions::NIL; //this is an error case
	else
	{
		sExpression * caar = input->getLeft()->getLeft();	
		sExpression * bi = evaluate(caar, a);
		if(bi->getString() == "T")
		{
			sExpression * cadar = input->getLeft()->getRight()->getLeft();
			sExpression * ei = evaluate(cadar, a);
		}
		else
		{
			evCond(input->getRight(), a);
		}
	}
}


sExpression * Evaluator::evList(sExpression * input, aList a)
{
	cout<<"\n inside evlist"<<endl;
	sExpression * res1 = PrimitiveFunctions::ISNULL(input);
	if(res1->getString() == "T")
	{// this is an error case
		cout<<"\n atom:"<<input->getString()<<endl;
		return PrimitiveFunctions::NIL;
	}
	else
	{
		cout<<"\n par1: L"<<endl;
		sExpression * par1 = evaluate(input->getLeft(), a);
		cout<<"\n par2: R"<<endl;
		sExpression * par2 = evList(input->getRight(), a);
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
                        cout<<"\nDefinition Found: "<<name<<endl;
                        return _dList.at(iter)->getRight();
                }
        }
        return  PrimitiveFunctions::NIL;
}

void Evaluator::add2DList(sExpression * f)
{
	_dList.push_back(f);
}
