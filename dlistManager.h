#ifndef DLISTMANAGER_H
#define DLISTMANAGER_H

#include "definitions.h"
#include "expressions.h"

class dlistManager
{
public:
	dlistManager();
	~dlistManager();

	sExpression * returnObject(string name);
private:
	
	std::vector<sExpression *> _dlist;
	primitives *primitivePtr;
}


#endif
