#include "definitions.h"
#include "parser.h"


int main()
{
	Parser p;
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
			output = p.Parse(input);
			cout<<"\n>>"<<output<<endl;
		}
		else
			keepRunning = false;
	}
	return 0;	
}

