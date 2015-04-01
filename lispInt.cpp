#include "definitions.h"
#include "parser.h"
#include "userdefines.h"
#include "primitives.h"

int main()
{
	userDefines def;
	Primitives prim;
	Parser *p = new Parser(&def, &prim);
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
		}
		else
			keepRunning = false;
	}
	return 0;	
}

