#ifndef CSE167_Group_h
#define CSE167_Group_h

#include "Node.h"
#include "Matrix4.h"
#include "Geode.h"

#include <vector>

using namespace std;

class Group : public Node 
{
public:
	vector<Node*> child;
	int numChild;

	Group();

	void addChild(Node*);

	virtual void draw(Matrix4) = 0;
};


#endif