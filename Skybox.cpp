#include "Skybox.h"
#include "glee.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <iostream>
using namespace std;

Skybox::Skybox(float size) : Drawable()
{
	this->size = size;
}

Skybox::~Skybox()
{
	//Delete any dynamically allocated memory/objects here
}

void Skybox::draw_ft(DrawData& data)
{
	float halfSize = size / 2.0;

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	Globals::ft.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	// Draw front face:
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, -halfSize);

	glEnd();

	Globals::ft.unbind();

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Skybox::draw_bk(DrawData& data)
{
	float halfSize = size / 2.0;

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	Globals::bk.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	// Draw back face:
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();

	Globals::ft.unbind();

	glPopMatrix();
	glEnable(GL_LIGHTING);

}

void Skybox::draw_lf(DrawData& data)
{
	float halfSize = size / 2.0;

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	Globals::lf.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	// Draw left side:
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();

	Globals::lf.unbind();

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Skybox::draw_rt(DrawData& data)
{
	float halfSize = size / 2.0;

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	Globals::rt.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, halfSize);

	glEnd();

	Globals::rt.unbind();

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Skybox::draw_up(DrawData& data)
{
	float halfSize = size / 2.0;

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	Globals::up.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, -halfSize);

	glEnd();

	Globals::up.unbind();

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Skybox::draw_dn(DrawData& data)
{
	float halfSize = size / 2.0;

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	Globals::dn.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 0); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();

	Globals::dn.unbind();

	glPopMatrix();
	glEnable(GL_LIGHTING);
}


void Skybox::update(UpdateData& data)
{
	//
}