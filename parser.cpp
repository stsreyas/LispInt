#include "parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

}

string Parser::Parse(string expression)
{
	StringPacket output;
	inputString = pruneString(expression);
	#if 0
	output = parseExpression(inputString);
	
	if(output.errorCode == 0)
		return output.s;
	#endif	
	return inputString;
}

// This is a recursive function
// It will take as input a string, check the first element and if it is an opening paren
// then it will call itself on a smaller string starting from the next element
// it will return on seeing a closing paren
// at each call it will have a list of acceptable tokens it can see and if it sees something else
// it will push out an error code and a null string.
StringPacket Parser::parseExpression(string expression)
{
	bool keepParsing = true;
	string stringSoFar;
	bool leftSeen = false;
	bool rightSeen = false;
	int length = expression.length();
	int strPtr = 0;
	StringPacket outPacket;
	while(keepParsing)
	{
		int offset = 1;
		int tokenId = checkToken(expression[strPtr]);
		strPtr += 1;
		switch(tokenId)
		{
			case 1:
			{	// opening paren	
				string subExpression = expression.substr(strPtr, (length-strPtr));
				StringPacket retPacket = parseExpression(subExpression);
				if(retPacket.errorCode == 1)
				{
					outPacket.errorCode = 1;
					return outPacket;
				}
				else
				{
					strPtr += retPacket.offset;
					stringSoFar += retPacket.s;
				}
				break;
			}
			case 2:
			{	// pointer		
				if(leftSeen == false)
				{
					outPacket.errorCode = 1;
					return outPacket;
				}
				break;
			}
			case 3:
			{	// whitespace
				if(leftSeen == false)
				{
					strPtr += 1;
				}
				else
				{
					
					string subExpression = expression.substr(strPtr, (length-strPtr));
					StringPacket retPacket = parseExpression(subExpression);

				}
				break;
			}
			case 4:
			{	// closing paren
				return outPacket;	
			}
			default:
			{	// identifier or number
				if(leftSeen == false)
				{
					leftSeen == true;
				}
				else
				{
					
					
				}
				break;			
			}
		}
	}
}

string Parser::generateExpression()
{


}


int Parser::checkToken(char ch)
{
	switch(ch)
	{	
		case '(':
			return 1;
		case '.':
			return 2;
		case ' ':
			return 3;
		case ')':
			return 4;
		default:
			return 0;
	}
}

// This function removes extra whitespaces and returns from the input string
string Parser::pruneString(string expression)
{
	string ret = "\n";
	string pruned;
	// prune return from string
	int startFrom = 0;
	int loc = 0;
	while(loc != std::string::npos)
	{
	   	loc = expression.find(ret, startFrom);
      		pruned += expression.substr(startFrom, (loc - startFrom));
		startFrom = loc + 1;
	}

	// prune multiple whitespaces from string
	startFrom = 0;
	loc = 0;
	string multSp = "  ";
	while(loc != std::string::npos)
	{
		int len = pruned.size();
		loc = pruned.find(multSp, startFrom);
		if(loc != std::string::npos)
			pruned = pruned.substr(startFrom, loc) + " " + pruned.substr(loc+2, len);	
	}
	return pruned;
}
