#include "parser.h"

Parser::Parser()
{
	_inputEncoded = NULL;
}

Parser::~Parser()
{

};

string Parser::Parse(string expression)
{
	outputString = "";
	inputString = "";
	if(_inputEncoded != NULL)
		delete _inputEncoded;
	inputString = pruneString(expression);
	bool status = encodeString(inputString);
	if(status)
	{
		ParamPacket out = evaluateExpression();
			if(out._errorCode == 0)
			{
				generateExpression();
				return outputString;
			}
			else
				return out._errorMessage;
	}
	return outputString;
}

bool Parser::encodeString(string input)
{
	int length = (int)input.length();
	_inputEncoded = new int [length];
	for(int i = 0; i < length; i++)
	{
		_inputEncoded[i] = checkToken(input[i]);
		if(_inputEncoded[i] == -1)
		{	
			cout<<">>Error: Invalid character at "<<i<<endl; 
			return false;
		}
	}
	return true;
}

ParamPacket Parser::evaluateExpression()
{
	ParamPacket output;
	expTree = new sExpression;
	if(_inputEncoded[0] == 1)
	{
		output = evaluate(1, expTree, false);
		if((output._errorCode == 0) && (output._strPtr < inputString.length()))
		{
			output._errorCode = 1;
			output._errorMessage += "Improper termination";
		}
	}
	else
	{	if(inputString.length() >= 1)
		{
			output._errorCode = 1;
			output._errorMessage += "Invalid starting symbol";
		}
	}
	return output;
}

// This is a recursive function
// It will take as input a string, check the first element and if it is an opening paren
// then it will call itself on a smaller string starting from the next element
// it will return on seeing a closing paren
// at each call it will have a list of acceptable tokens it can see and if it sees something else
// it will push out an error code and a null string.
ParamPacket Parser::evaluate(int strPtr, sExpression * parent, bool listFlag)
{
	//cout<<inputString;
	ParamPacket output;
	bool keepRunning = true;
	int numExpressions = 0;
	output._isList = listFlag;
	while(keepRunning)
	{
		int curCode = _inputEncoded[strPtr];
		int prevCode = _inputEncoded[strPtr-1];
		if(!TRANSITION[curCode][prevCode])
		{
			output._errorCode = 1;
			output._errorMessage += TOKENCODE[prevCode] + " cannot precede " + TOKENCODE[curCode];
			return output;
		}
		if(_inputEncoded[strPtr] == 1)
		{
			sExpression * child = parent->initLeaf();
			ParamPacket retPacket = evaluate(strPtr + 1, child, false);
			if(retPacket._errorCode == 1)
			{
				output = retPacket;
				return output;
			}
			else
				strPtr = retPacket._strPtr;
		}
		else if(_inputEncoded[strPtr] == 3)
		{
			if(output._pointerSeen)
			{
				output._errorCode = 1;
				output._errorMessage += "Invalid whitespace used";
				return output;
			}
			output._isList = true;
			sExpression * child = parent->initLeaf();
			ParamPacket retPacket = evaluate(strPtr + 1, child, output._isList);
			if(retPacket._errorCode == 1)
			{
				output = retPacket;
				return output;
			}
			else
				output._strPtr = retPacket._strPtr;
			return output;
		}
		else if(_inputEncoded[strPtr] == 2)
		{	
			if((numExpressions > 1)||(listFlag == true))
			{
				output._errorCode = 1;
				output._errorMessage += "Invalid pointer used";
				return output;
			}
			output._pointerSeen = true;
			strPtr++;
		}
		else if(_inputEncoded[strPtr] == 4)
		{
			if((numExpressions <=1) && (output._pointerSeen == false))
				output._isList = true;
			if((output._isList == true))// || (parent->left == NULL))
			{
				sExpression * child = parent->initLeaf();
				child->setString("NIL");
			}
			output._strPtr = ++strPtr;
			return output;			
		}
		else
		{	// create a new atomic sExpression
			numExpressions++;
			sExpression * child = parent->initLeaf();
			string atomic;
			while(_inputEncoded[strPtr] == 0)
				atomic += inputString[strPtr++];
			child->setString(atomic);
		}
		if(strPtr >= inputString.length())
		{
			keepRunning = false;
			output._errorCode = 1;
			output._errorMessage += "Closing Paren Not Found";
			return output;
		}
	}
}

void Parser::generateExpression()
{
	traverseAndGenerate(expTree);
}

void Parser::traverseAndGenerate(sExpression * parent)
{
	if(parent->getType() == ATOMIC)
	{
		outputString += parent->getString();
		return;	
	}
	else
	{
		outputString += "(";
		if(parent->getLeft() != NULL)
			traverseAndGenerate(parent->getLeft());
		if(parent->getRight() != NULL)
		{
			outputString += ".";
			traverseAndGenerate(parent->getRight());
		}
		outputString += ")";
		return;
	}
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
				(chCode >= 65 && chCode <= 90) || (chCode >= 97 && chCode <=122) ||
				(chCode == 45))
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

	pruned = pruneCharacters(pruned, "  ", " ");
	pruned = pruneCharacters(pruned, " .", ".");
	pruned = pruneCharacters(pruned, ". ", ".");
	pruned = pruneCharacters(pruned, "( ", "(");
	pruned = pruneCharacters(pruned, " )", ")");

	return pruned;
}

string Parser::pruneCharacters(string input, string str2Find, string strReplace)
{
	string output;
	int startFrom = 0;
	int loc = 0;
	int expLength = str2Find.length();
	while(loc != (int)std::string::npos)
	{
		int len = input.size();
		loc = input.find(str2Find, startFrom);
		if(loc != (int)std::string::npos)
			input = input.substr(startFrom, loc) + strReplace + input.substr(loc+expLength, len);
	}
	output = input;
	return output;
}
