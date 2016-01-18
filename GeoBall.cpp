#include "GeoBall.h"
#include "glee.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "Globals.h"

using namespace std;

void GeoBall::render(Matrix4 m)
{
	glColor4f(0.2, 0.2, 0.2, 1);
	GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);


	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(m.ptr());

	gluSphere(sphere, 2, 50, 50);

	glPopMatrix();
}