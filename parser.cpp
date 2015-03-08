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
	StringPacket output;
	outputString = "";
	inputString = "";
	if(_inputEncoded != NULL)
		delete _inputEncoded;
	inputString = pruneString(expression);
	#if 1
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
	#else
	if(inputString[0] == '(')
	{
		int len = inputString.length();
		expTree = new sExpression;
		outputString = "";
		output = parseExpression(inputString.substr(1, len), false, expTree, 1);
		//output = parseExpression(inputString, false, expTree, 1);
		if(output.errorCode == 0)
		{
			generateExpression();	
			return outputString;
		}
		else
			return "The Force Is NOT With You";
	}
	else
	{
		return "Somebody gonna get hurt real bad";
	}
	#endif	
}

#if 0
// This function generates a skip code
// which corresponds to the length of the subexp it is a part of
void Parser::generateSkipCode(string encoded)
{
	int ctr = 0;
	int length = encoded.length();
	bool keepRunning = true;
	if(encoded[ctr] == 1)
	{	
		while(keepRunning)	
		{
		
		}
	}
}
#endif

bool Parser::encodeString(string input)
{
	int length = (int)input.length();
	_inputEncoded = new int [length];
	for(int i = 0; i < length; i++)
	{
		_inputEncoded[i] = checkToken(input[i]);
		if(_inputEncoded[i] == -1)
		{	
			cout<<"Invalid character "<< i<<endl; 
			return false;
		}
	}
	return true;
}

#if 0
bool checkTransition(int curPtr)
{
	
}
#endif

ParamPacket Parser::evaluateExpression()
{
	ParamPacket output;
	expTree = new sExpression;
	if(_inputEncoded[0] == 1)
	{
		output = evaluate(1, expTree, false);
	}
	else
	{
		output._errorCode = 1;
		output._errorMessage = "Invalid starting symbol";
	}
	return output;
}

ParamPacket Parser::evaluate(int strPtr, sExpression * parent, bool listFlag)
{
	//cout<<inputString;
	ParamPacket output;
	bool keepRunning = true;
	int numExpressions = 0;
	output._isList = listFlag;
	while(keepRunning)
	{
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
			// only valid when there is only 1 sExpression so far
			if(numExpressions > 1)
			{
				output._errorCode = 1;
				string err = "invalid . used";
				output._errorMessage = err;
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
			output._errorMessage = "Closing Paren Not Found";
			return output;
		}
	}
}

// This is a recursive function
// It will take as input a string, check the first element and if it is an opening paren
// then it will call itself on a smaller string starting from the next element
// it will return on seeing a closing paren
// at each call it will have a list of acceptable tokens it can see and if it sees something else
// it will push out an error code and a null string.
StringPacket Parser::parseExpression(string expression, bool listFlag, sExpression * parent, int prevToken)
{
	bool keepParsing = true;
	//sExpression * leftChild = parent->left;
	//sExpression * rightChild = parent->right;
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
				// valid when it follows a space, pointer or another paren
				#ifdef LOG
				cout<<"\nrec1\n";
				#endif
				if(prevToken == 0)
				{
					outPacket.errorCode = 1;
					return outPacket;
				}
			//	if(prevToken != 3)
			//	{
				string subExpression = expression.substr(strPtr, (length-strPtr));
				sExpression * child = parent->initLeaf();
				if(child == NULL)
				{	
					cout<<"Something is wrong!!!\n";
					outPacket.errorCode = 1;
					return outPacket;
				}
				prevToken = 1;	
				StringPacket retPacket = parseExpression(subExpression, false, child, 1);
				if(retPacket.errorCode == 1)
				{
					outPacket.errorCode = 1;
					return outPacket;
				}
				else
				{
					strPtr += retPacket.offset;
					//cout<<"ptr="<<strPtr<<endl;
				}
			//	}
				break;
			}
			case 2:
			{	// pointer		
				// valid when it follows a idn or closing paren only when there hasnt
				// been another pointer at this level of the recursion
				prevToken = 2;
				if(((leftSeen == false) && parent->left == NULL) || (leftSeen == true && rightSeen == true)
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
					pointerSeen = true;
					if((parent->left == NULL))
					{
						sExpression * child = parent->initLeaf();
						child->setString(stringSoFar);
					}
					stringSoFar = "";
				}
				break;
			}
			case 3:
			{	// whitespace
				// valid when it follows an idn, closing paren and no pointer seen
				// at this level of the recursion
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
					#ifdef LOG
					cout<<"\nrec2\n";	
					#endif
					if(parent->left == NULL)
					{
						cout<<"MM\n";
						sExpression * child1 = parent->initLeaf();
						child1->setString(stringSoFar);
						stringSoFar = "";
					}
					sExpression * child2 = parent->initLeaf();
					//rightGrandChild = rightChild->initLeaf();
					if(child2 == NULL)
						cout<<"Something is Wrong!!\n!";
					string subExpression = expression.substr(strPtr, (length-strPtr));
					StringPacket retPacket = parseExpression(subExpression, isList, child2, 3);
					if(retPacket.errorCode == 1)
					{
						outPacket.errorCode = 1;
						return outPacket;
					}	
					else
					{
						strPtr += retPacket.offset;
						cout<<"ptr="<<strPtr<<endl;
					}

					prevToken = 3;
				}
				break;
			}
			case 4:
			{	// closing paren - Need to handle improper use of this better!!
				// valid only when an opening paren seen before
				if(expression[strPtr-2] != ')')
				{
					sExpression * child = parent->initLeaf();
					child->setString(stringSoFar);
				}
				if(isList);
				{
					cout<<"here\n";
					sExpression * lastChild = parent->initLeaf();
					lastChild->setString("NIL");
					cout<<"not Here\n";
				}
				prevToken = 4;
				outPacket.s = stringSoFar;
				outPacket.offset = strPtr;
				return outPacket;	
			}
			case 0:
			{	// identifier or number
				if(pointerSeen == false)
				{
					leftSeen = true;
					stringSoFar += cur;
					prevToken = 0;
				}
				else
				{
					rightSeen = true;
					stringSoFar += cur;
					prevToken = 0;
				}
				break;			
			}
			default:
			{
				outPacket.errorCode = 1;
				return outPacket;
			}
		}
	if(strPtr >= length)
	{	
		outPacket.offset = strPtr;
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

#if 0
ParamPacket Parser::parseExpression(ParamPacket input)
{

	bool keepParsing = true;
	sExpression * leftChild = input.parent->left;
	sExpression * rightChild = input.parent->right;
	string stringSoFar;
	bool pointerSeen = false;
	bool isList = listFlag;
	int length = expression.length();
	int strPtr = 0;
	ParamPacket output;
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
				// valid when it follows a space, pointer or another paren
				#ifdef LOG
				cout<<"\nrec1\n";
				#endif
				string subExpression = expression.substr(strPtr, (length-strPtr));
				leftChild = new sExpression;
				//child->setString(stringSoFar);
				if(leftChild == NULL)
				{	
					cout<<"Something is wrong!!!\n";
					outPacket.errorCode = 1;
					return outPacket;
				}
					
				StringPacket retPacket = parseExpression(subExpression, false, leftChild);
				if(retPacket.errorCode == 1)


}
#endif


void Parser::generateExpression()
{
	traverseAndGenerate(expTree);
	//return outputString;
}


void Parser::traverseAndGenerate(sExpression * parent)
{
	if(parent->type == ATOMIC)
	{
		outputString += parent->s;
		return;	
	}
	else
	{
		outputString += "(";
		if(parent->left != NULL)
			traverseAndGenerate(parent->left);
		if(parent->right != NULL)
		{
			outputString += ".";
			traverseAndGenerate(parent->right);
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
