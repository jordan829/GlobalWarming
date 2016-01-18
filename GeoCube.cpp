#include "GeoCube.h"
#include "glee.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "Globals.h"

using namespace std;

void GeoCube::render(Matrix4 m) 
{	
	/*glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glMultMatrixf(m.ptr());
	glutSolidCube(1);
	glPopMatrix();*/

	//cout << "drawing" << endl;
	float halfSize = .5;
	
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glColor3f(1, 1, 1);
	glMultMatrixf(m.ptr());

	glBegin(GL_QUADS);

	// Draw front face:
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(0, 0); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, -halfSize, halfSize);

	// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);

	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();
	glPopMatrix();
}