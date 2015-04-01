#include "definitions.h"
#include "parser.h"
#include "userdefines.h"
#include "primitives.h"
#include "evaluator.h"

int main()
{
	userDefines def;
	Primitives prim;
	Parser *p = new Parser(&def, &prim);
	Evaluator eval;
	
	string expression;	
	bool keepRunning = true;
	while(keepRunning)
	{
		string input;
		string output;
		cout<<">";
		getline(cin, input, '$');
		if(input.length() > 0)
		{
			output = p->Parse(input);
			cout<<"\n>>"<<output<<endl;
			sExpression * parsed = p->getParsedExpression();
			sExpression * evaled = eval.eval(parsed);
			p->traverseAndGenerate(evaled);
			string evString = p->getOutputString();
			cout<<"\n>>"<<evString<<endl;
		}
		else
			keepRunning = false;
	}
	return 0;	
}

