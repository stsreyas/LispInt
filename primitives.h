#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "definitions.h"
#include "expressions.h"
#include "primitivefunctions.h"

using namespace PrimitiveFunctions;

class Primitives
{
public:
	Primitives();
	~Primitives();
	sExpression * returnObject(string name);
	
private:

	std::vector<sExpression *> _list;
};

#endif
