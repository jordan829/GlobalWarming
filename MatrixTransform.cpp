#include "MatrixTransform.h"

#include <string>
#include <iostream>
#include "Globals.h"

using namespace std;

MatrixTransform::MatrixTransform() 
{
	Matrix4 i = Matrix4();
	i.identity();
	m = Matrix4(i);
}

MatrixTransform::MatrixTransform(Matrix4 matrix) 
{
	m = Matrix4(matrix);
}

void MatrixTransform::setTransformationMatrix(Matrix4 matrix) 
{
	m = Matrix4(matrix);
}

Matrix4 MatrixTransform::getTransformationMatrix() 
{
	return m;
}

void MatrixTransform::draw(Matrix4 c) 
{
	c = c.multiply(m);
	for (int i = 0; i < numChild; i++)
	{
		child[i]->draw(c);
	}
}