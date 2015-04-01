#include "userdefines.h"

userDefines::userDefines()
{


}


userDefines::~userDefines()
{
	int size = _defs.size();
	if(size != 0)
		_defs.clear();
}

sExpression * userDefines::returnObject(string name)
{
	std::vector<sExpression *>::size_type iter;
	std::transform(name.begin(), name.end(), name.begin(), ::toupper); 
	//check primitives
	for(iter = 0; iter != _defs.size(); iter++)
	{
		string str = _defs.at(iter)->getString();
		std::transform(str.begin(), str.end(),str.begin(), ::toupper);
		if(str == name)
		{
			return _defs.at(iter);
		}
	}
	// no existing sExpression found so create a new one
	sExpression * exp = new sExpression(name);
	_defs.push_back(exp);
	return  _defs.back();
}
