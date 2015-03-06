#include "definitions.h"
#include "parser.h"


bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
int main()
{
	Parser p;
	string expression;	
	bool expressionIncomplete = true;
	while(expressionIncomplete)
	{
		string input;
		string output;
		cout<<">";
		getline(cin, input, '$');
		//cout<<">>"<<input;
	//	output = p.Parse(input);

#if 0
	std::string::iterator new_end = std::unique(input.begin(), input.end(), BothAreSpaces);
	input.erase(new_end, input.end());
	output = input;
	cout<<">>"<<output;
#endif
#if 1
		string multSp = "  ";
		int start = 0;
		int loc = 0;
		for(int i = 0; i < 3; i++)
	//	while(loc != std::string::npos)
		{
			int len = input.length();
			cout<<len;
			loc = input.find(multSp, start);
			//cout<<loc<<endl;
			string temp = output.substr(start, loc-1) + output.substr(loc+1, len);
			output = temp;
			cout<<">>"<<output<<endl;
		}
#endif
			
	}
	return 0;	
}

