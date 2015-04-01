#ifndef USERDEFINES_H
#define USERDEFINES_H

#include "definitions.h"
#include "expressions.h"

class userDefines
{
public:
	userDefines();
	~userDefines();

	sExpression * returnObject(string name);
	sExpression * returnExisting(string name);
private:

	std::vector<sExpression *> _defs;

};

#endif
