#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

struct node
{
	node()
	{
		value = 0;
		left = NULL;
		right = NULL;
	}
	int value;
	node * left;
	node * right;
}

class sExpressions
{
public:
	sExpressions();
	~sExpressions();
	void insert(int id);
	void insert(node * head);
	
	

private:

	

}


#endif
