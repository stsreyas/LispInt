#include "primitives.h"

Primitives::Primitives()
{
	sExpression * car = new sExpression("CAR");
	sExpression * cdr = new sExpression("CDR");
	sExpression * cons = new sExpression("CONS");
	sExpression * atom = new sExpression("ATOM");
	sExpression * eq = new sExpression("EQ");
	sExpression * null = new sExpression("NULL");
	sExpression * isInt = new sExpression("INT");
	sExpression * plus = new sExpression("PLUS");
	sExpression * minus = new sExpression("MINUS");
	sExpression * times = new sExpression("TIMES");
	sExpression * quotient = new sExpression("QUOTIENT");
	sExpression * remainder = new sExpression("REMAINDER");
	sExpression * less = new sExpression("LESS");
	sExpression * greater = new sExpression("GREATER");
	sExpression * cond = new sExpression("COND");
	sExpression * quote = new sExpression("QUOTE");
	sExpression * defun = new sExpression("DEFUN");

	_list.push_back(PrimitiveFunctions::T);
	_list.push_back(PrimitiveFunctions::NIL);
	_list.push_back(car);
	_list.push_back(cdr);
	_list.push_back(cons);
	_list.push_back(atom);
	_list.push_back(eq);
	_list.push_back(null);
	_list.push_back(isInt);
	_list.push_back(plus);
	_list.push_back(minus);
	_list.push_back(times);
	_list.push_back(quotient);
	_list.push_back(remainder);
	_list.push_back(less);
	_list.push_back(greater);
	_list.push_back(cond);
	_list.push_back(quote);
	_list.push_back(defun);	
}

Primitives::~Primitives()
{

}


sExpression * Primitives::returnObject(string name)
{
	std::vector<sExpression *>::size_type iter;
        std::transform(name.begin(), name.end(), name.begin(), ::toupper);
        //check primitives
        for(iter = 0; iter != _list.size(); iter++)
        {
                string str = _list.at(iter)->getString();
                std::transform(str.begin(), str.end(),str.begin(), ::toupper);
                if(str == name)
                {
			cout<<"\nReturned primitive "<<name<<endl;
                        return _list.at(iter);
                }
        }
	return NULL;
}

