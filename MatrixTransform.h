#ifndef CSE167_MatrixTransform_h
#define CSE167_MatrixTransform_h

#include "Group.h"
#include "Matrix4.h"

#include <string>

using namespace std;

class MatrixTransform : public Group 
{
public:
	Matrix4 m;

	MatrixTransform();
	MatrixTransform(Matrix4);

	void setTransformationMatrix(Matrix4);
	Matrix4 getTransformationMatrix();
	virtual void draw(Matrix4);
};

#endif