#include "definitions.h"
#include "parser.h"


//bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
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
		output = p.Parse(input);
		cout<<">>"<<output<<endl;
#if 0
	std::string::iterator new_end = std::unique(input.begin(), input.end(), BothAreSpaces);
	input.erase(new_end, input.end());
	output = input;
#endif
#if 0
		string multSp = "  ";
		int start = 0;
		int loc = 0;
		//cout<<"bleh\n";
		//cout<<input.length();
		//cout<<"bleh2\n";
		//cout<<input.size();
		output = input;
	//	for(int i = 0; i < 3; i++)
		while(loc != std::string::npos)
		{
	//		cout<<"inside\n"<<flush;
			int len = output.size();
	//		cout<<len<<endl<<flush;
			loc = output.find(multSp, start);
			if(loc != std::string::npos)
			{
	//		cout<<loc<<endl;
			string temp1 = output.substr(start, loc);
	//		cout<<temp1<<endl;
			string temp2 = output.substr(loc+2, len);
	//		cout<<temp2<<endl;
			output = temp1 + temp2;
			//string temp = output.substr(start, loc-1) + output.substr(loc+1, len);
			//output = temp;
			cout<<">>"<<output<<endl;
			}
		}
#endif
			
	}
	return 0;	
}

