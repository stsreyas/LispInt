#include "parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

}

// This is a recursive function
// It will take as input a string, check the first element and if it is an opening paren
// then it will call itself on a smaller string starting from the next element
// it will return on seeing a closing paren
// at each call it will have a list of acceptable tokens it can see and if it sees something else
// it will push out an error code and a null string.
string Parser::parseExpression(string expression)
{



}

string Parser::generateExpression()
{


}



