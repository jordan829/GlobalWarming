#ifndef CSE167_Node_h
#define CSE167_Node_h

#include "Matrix4.h"

#include <iostream>
using namespace std;

class Node 
{
public:
	Node *parent;

	Node();
	
	void setParent(Node*);

	virtual void draw(Matrix4 m) = 0;
};

#endif