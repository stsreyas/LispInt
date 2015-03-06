#include "parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

};

string Parser::Parse(string expression)
{
	StringPacket output;
	inputString = pruneString(expression);
	#if 1
	if(inputString[0] == '(')
	{
		int len = inputString.length();
		expTree = new sExpression;
		output = parseExpression(inputString.substr(1, len), false, expTree);
		if(output.errorCode == 0)
			return inputString;
		else
			return "The Force Is NOT With You";
	}
	else
	{
	#endif	
		return "Somebody gonna get hurt real bad";
	}
}

// This is a recursive function
// It will take as input a string, check the first element and if it is an opening paren
// then it will call itself on a smaller string starting from the next element
// it will return on seeing a closing paren
// at each call it will have a list of acceptable tokens it can see and if it sees something else
// it will push out an error code and a null string.
StringPacket Parser::parseExpression(string expression, bool listFlag, sExpression * parent)
{
	bool keepParsing = true;
	string stringSoFar;
	bool leftSeen = false;
	bool rightSeen = false;
	bool pointerSeen = false;
	bool isList = listFlag;
	int length = expression.length();
	int strPtr = 0;
	StringPacket outPacket;
	while(keepParsing)
	{
		char cur = expression[strPtr];
		int tokenId = checkToken(cur);
		#ifdef LOG
		cout<<endl<<expression[strPtr]<<"="<<tokenId;
		#endif
		strPtr += 1;
	
		switch(tokenId)
		{
			case 1:
			{	// opening paren
				#ifdef LOG
				cout<<"\nrec1\n";
				#endif
				stringSoFar += cur;	
				string subExpression = expression.substr(strPtr, (length-strPtr));
				sExpression * child = parent->initLeaf();
				if(child == NULL)
					cout<<"Something is wrong!!!\n";
					
				StringPacket retPacket = parseExpression(subExpression, false, child);
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
				if((leftSeen == false) || (leftSeen == true && rightSeen == true)
					|| (isList == true))
				{
					outPacket.errorCode = 1;
					#ifdef LOG
					cout<<"\nerr1\n";
					#endif
					return outPacket;
				}
				else
				{
					stringSoFar += cur;
					pointerSeen = true;
				}
				break;
			}
			case 3:
			{	// whitespace
				if(pointerSeen == true)
				{
					outPacket.errorCode = 1;
					#ifdef LOG
					cout<<"\nerr2\n";
					#endif
					return outPacket;	
				}
				else
				{
				isList = true;
				stringSoFar += ".(";
				#ifdef LOG
				cout<<"\nrec2\n";	
				#endif
				sExpression * child = parent->initLeaf();
				if(child == NULL)
					cout<<"Something is Wrong!!\n!";
				string subExpression = expression.substr(strPtr, (length-strPtr));
				StringPacket retPacket = parseExpression(subExpression, isList, child);
				if(retPacket.errorCode == 1)
				{
					outPacket.errorCode = 1;
					return outPacket;
				}
				else
				{
					strPtr += retPacket.offset;
					stringSoFar += retPacket.s;
					stringSoFar += ".NIL)";
				}

				}
				break;
			}
			case 4:
			{	// closing paren - Need to handle improper use of this better!!
				stringSoFar += cur;
				outPacket.offset = strPtr;
				outPacket.s = stringSoFar;
				return outPacket;	
			}
			case 0:
			{	// identifier or number
				if(pointerSeen == false)
				{
					leftSeen = true;
					stringSoFar += cur;
				}
				else
				{
					rightSeen = true;
					stringSoFar += cur;
				}
				break;			
			}
			default:
			{
				
			}
		}
	if(strPtr >= length)
	{
		outPacket.s = stringSoFar;
		keepParsing = false;
	}
	}
	if(!isList)
	{
		outPacket.errorCode = 1;
		cout<<"\nimproper end\n";
	}
	return outPacket;
}

string Parser::generateExpression()
{


}


int Parser::checkToken(char ch)
{
	switch(ch)
	{	
		case '(':
			{return 1;}
		case '.':
			{return 2;}
		case ' ':
			{return 3;}
		case ')':
			{return 4;}
		default:
		{
			int chCode = (int)ch;
			if((chCode >= 48 && chCode <= 57) ||
				(chCode >= 65 && chCode <= 90) || (chCode >= 97 && chCode <=122))
				return 0;
			else	
				return -1;
		}
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
	
	// prune remaining spaces
	startFrom = 0;
	loc = 0;
	string spDot = " .";
	while(loc != std::string::npos)
	{
		int len = pruned.size();
		loc = pruned.find(spDot, startFrom);
		if(loc != std::string::npos)
			pruned = pruned.substr(startFrom, loc) + "." + pruned.substr(loc+2, len);
	}
	
	startFrom = 0;
	loc = 0;
	string dotSp = ". ";
	while(loc != std::string::npos)
	{
		int len = pruned.size();
		loc = pruned.find(dotSp, startFrom);
		if(loc != std::string::npos)
			pruned = pruned.substr(startFrom, loc) + "." + pruned.substr(loc+2, len);
	}
	
	startFrom = 0;
	loc = 0;
	string brSp = "( ";
	while(loc != std::string::npos)
	{
		int len = pruned.size();
		loc = pruned.find(brSp, startFrom);
		if(loc != std::string::npos)
			pruned = pruned.substr(startFrom, loc) + "(" + pruned.substr(loc+2, len);
	}

	
	startFrom = 0;
	loc = 0;
	string spBr = " )";
	while(loc != std::string::npos)
	{
		int len = pruned.size();
		loc = pruned.find(spBr, startFrom);
		if(loc != std::string::npos)
			pruned = pruned.substr(startFrom, loc) + ")" + pruned.substr(loc+2, len);
	}

	return pruned;
}
