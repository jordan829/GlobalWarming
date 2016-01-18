#include "Node.h"

Node::Node() 
{
	parent = NULL;
}

void Node::setParent(Node *p) 
{
	parent = p;
}