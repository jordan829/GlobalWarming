#include "Cone.h"
#include "glee.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Cone::Cone(double base, double height, int slices, int stacks) : Drawable()
{
	this->base = base;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
}

void Cone::draw(DrawData& data)
{
	material.apply();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	glutSolidCone(base, height, slices, stacks);

	glPopMatrix();
}


void Cone::update(UpdateData& data)
{
	//
}