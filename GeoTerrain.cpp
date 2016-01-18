#include "GeoTerrain.h"
#include "glee.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "Globals.h"

using namespace std;

void GeoTerrain::render(Matrix4 m)
{
	float x0, y0, z0;
	float x1, y1, z1;
	float x2, y2, z2;
	float c0, c1;
	Vector3 v0, v1, v2;
	Vector3 norm;

	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();

	glMultMatrixf(m.ptr());

	Globals::shader->bind();

	//Only draw vertices (extra, more responsive)
	if (!Globals::drawPoints)	
	{
		glColor3f(1, 1, 1);
		glBegin(GL_POINTS);

		//Reduce # of vertices for faster rendering
		for (int i = 0; i < GRID_DIMENSION; i += 4)
		{
			for (int j = 0; j < GRID_DIMENSION; j += 4)
			{
				x0 = -(i - 512) / 4;
				y0 = ((Globals::verts[i][j][1]) / 4) * Globals::elevationScale;
				z0 = -(j - 512) / 4;
	
				glVertex3f(x0, y0, z0);
			}
		}

		glEnd();
	}

	else
	{
		int water = glGetUniformLocation(Globals::shader->getPid(), "waterLevel");
		glUniform1f(water, Globals::currWater / 4);

		int height = glGetUniformLocation(Globals::shader->getPid(), "maxHeight");
		glUniform1f(height, Globals::maxHeight * Globals::elevationScale);

		//Render triangle mesh in snake-like pattern
		//left to right -> move up -> right to left -> move up -> repeat
		for (float y = 0; y < GRID_DIMENSION - 1; y++)
		{
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(0.5, 0.5, 0.5);
			//Traverse row left to right
			for (float x = 0; x < GRID_DIMENSION; x++)
			{
				//-x and -z equal to rotation of 180 degrees
				x0 = -(x - 512) / 4;
				y0 = ((Globals::verts[x][y + 1][1]) / 4) * Globals::elevationScale;
				z0 = -(y + 1 - 512) / 4;

				x1 = -(x - 512) / 4;
				y1 = ((Globals::verts[x][y][1]) / 4) * Globals::elevationScale;
				z1 = -(y - 512) / 4;

				glNormal3f(Globals::norms[x][y][0], Globals::norms[x][y][1], Globals::norms[x][y][2]);
				glVertex3f(x0, y0, z0);
				glVertex3f(x1, y1, z1);
			}

			glEnd();
		}
	}
	Globals::shader->unbind();

	glPopMatrix();
}