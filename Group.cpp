#include "Group.h"

#include <vector>
#include <iostream>

using namespace std;

Group::Group() 
{
	child.clear();
	numChild = 0;
}

void Group::addChild(Node *n) 
{
	child.push_back(n);
	n->setParent(this);
	numChild++;
}