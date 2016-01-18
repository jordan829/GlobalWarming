#ifndef CSE167_Geode_h
#define CSE167_Geode_h
#include "glee.h"
#include "Node.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include <GL/glut.h>

using namespace std;

class Geode : public Node 
{
public:
	Matrix4 modelview;

	Geode();

	virtual void render(Matrix4) = 0;
	void draw(Matrix4);
};

#endif