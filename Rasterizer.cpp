#ifdef _WIN32
#include <windows.h>
#endif
#include "glee.h"
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Matrix4.h"
#include "Camera.h"
#include "Rasterizer.h"
#include "Globals.h"
#include "OBJObject.h"

#define PI 3.14159265358979323846

static Matrix4 viewport; 
static Matrix4 projection;

int active_obj = 1;

using namespace std;

Rasterizer::Rasterizer(void)
{
	setViewport(window_width, window_height);
	setProjection();
}

void Rasterizer::setViewport(int width, int height)
{
	int x = width;
	int y = height;

	viewport = Matrix4(x / 2, 0, 0, 0,
						0, y / 2, 0, 0,
						0, 0, 0.5, 0,
						x / 2, y / 2, 0.5, 1);
}

void Rasterizer::setProjection(void)
{
	float fov = 60.0;
	float aspect = (double) window_width / (double) window_height;
	float nearz = 1.0;
	float farz = 1000.0;
	float rad = (fov / 2) * (PI / 180);

	projection = Matrix4( 1 / (aspect * tan(rad)), 0, 0, 0,
						0, 1 / tan(rad), 0, 0,
						0, 0, (nearz + farz) / (nearz - farz), -1,
						0, 0, (2 * (nearz * farz)) / (nearz - farz), 0 );
}

void Rasterizer::loadData() // Needed?????
{
	// put code to load data model here
	
}

void Rasterizer::loadCube(void) // Case 1
{
	numVert = 72;  // 6 faces * 4 vertices * 3 coordinates
	numIndex = 36; // 6 faces * 2 triangles * 3 vertices

	vertices.resize(numVert);
	colors.resize(numVert);
	indices.resize(numIndex);

	for (int i = 0; i < numVert; i++) 
	{
		vertices[i] = cube_vertices[i];
		colors[i] = cube_colors[i];
	}

	for (int i = 0; i < numIndex; i++) 
	{
		indices[i] = cube_indices[i];
	}
}

void Rasterizer::loadHouse(void) // Case 2 / 3
{
	numVert = 126;
	numIndex = 60;

	vertices.resize(numVert);
	colors.resize(numVert);
	indices.resize(numIndex);

	for (int i = 0; i < numVert; i++) 
	{
		vertices[i] = house_vertices[i];
		colors[i] = house_colors[i];
	}

	for (int i = 0; i < numIndex; i++) 
	{
		indices[i] = house_indices[i];
	}
}

void Rasterizer::loadObj(OBJObject obj) // Case 4 / 5 / 6
{
	
}

// Clear frame buffer
void Rasterizer::clearBuffer(void) 
{
	Color clearColor = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < window_width * window_height; ++i)
	{ 
		pixels[i * 3] = clearColor[0];
		pixels[i * 3 + 1] = clearColor[1];
		pixels[i * 3 + 2] = clearColor[2];
	}

	initialize_zbuffer();
}

void Rasterizer::initialize_zbuffer(void)
{
	fill_n(zbuffer, window_width*window_height, 1);
}

// Draw a point into the frame buffer
void Rasterizer::drawPoint(int x, int y, float r, float g, float b)
{
	if (x >= 0 && y >= 0 && x < window_width && y < window_height)
	{
		int offset = y * window_width * 3 + x * 3;
		pixels[offset] = r;
		pixels[offset + 1] = g;
		pixels[offset + 2] = b;
	}
}

void Rasterizer::update_zbuffer(int x, int y, float c1, float c2, float c3, float z)
{
	int offset = y * window_width + x;
	if (x >= 0 && y >= 0 && x < window_width && y < window_height && z < zbuffer[offset]) 
	{
		zbuffer[offset] = z;
		drawPoint(x, y, c1, c2, c3);
	}
}

void Rasterizer::rasterizeTriangle(Vector4 a, Vector4 b, Vector4 c, float c1, float c2, float c3)
{
	float alpha, beta, gamma, denom;

	float x1 = a[0];
	float y1 = a[1];

	float x2 = b[0];
	float y2 = b[1];

	float x3 = c[0];
	float y3 = c[1];

	float top = max(max(y1, y2), y3);
	if (top >= window_height)
		top = window_height - 1;

	float bottom = min(min(y1, y2), y3);
	if (bottom < 0)
		bottom = 0;

	float left = min(min(x1, x2), x3);
	if (left < 0)
		left = 0;

	float right = max(max(x1, x2), x3);
	if (right >= window_width)
		right = window_width - 1;

	for (int row = bottom; row <= top; row++)
	{
		for (int col = left; col <= right; col++)
		{
			Vector3 v0 = Vector3(x3 - x1, y3 - y1, 0);
			Vector3 v1 = Vector3(x2 - x1, y2 - y1, 0);
			Vector3 v2 = Vector3(col - x1, row - y1, 0);

			denom = v0.dot(v0) * v1.dot(v1) - v0.dot(v1) * v1.dot(v0);

			alpha = (v1.dot(v1) * v2.dot(v0) - v1.dot(v0) * v2.dot(v1)) / denom;
			beta = (v0.dot(v0) * v2.dot(v1) - v0.dot(v1) * v2.dot(v0)) / denom;
			gamma = 1 - alpha - beta;

			Vector3 P = a.toVector3() + (c - a).toVector3().scale(alpha) + (b - a).toVector3().scale(beta);
			float z = P[2];

			if (Globals::interp)
			{
				c1 = row / c1;
				c2 = col / c2;
				c3 = z / c3;
			}

			if (alpha > 0 && alpha < 1 && beta > 0 && beta < 1 && gamma > 0 && gamma < 1)
			{
				if (Globals::zbuf)
				{
					update_zbuffer(col, row, c1, c2, c3, z);
				}
				else
					drawPoint(col, row, c1, c2, c3);
			}
		}
	}
}

void Rasterizer::rasterizeVertices(Vector4 p1, Vector4 p2, Vector4 p3, float color1, float color2, float color3)
{
	Vector4 tmp1 = Globals::object->toWorld.multiply(p1);
	Vector4 tmp2 = Globals::camera.getInverseMatrix().multiply(tmp1);
	Vector4 tmp3 = projection.multiply(tmp2);
	tmp3 = tmp3.dehomogenize();
	Vector4 a = viewport.multiply(tmp3);

	tmp1 = Globals::object->toWorld.multiply(p2);
	tmp2 = Globals::camera.getInverseMatrix().multiply(tmp1);
	tmp3 = projection.multiply(tmp2);
	tmp3 = tmp3.dehomogenize();
	Vector4 b = viewport.multiply(tmp3);

	tmp1 = Globals::object->toWorld.multiply(p3);
	tmp2 = Globals::camera.getInverseMatrix().multiply(tmp1);
	tmp3 = projection.multiply(tmp2);
	tmp3 = tmp3.dehomogenize();
	Vector4 c = viewport.multiply(tmp3);

	rasterizeTriangle(a, b, c, color1, color2, color3);
}

void Rasterizer::rasterize1Vertex(Vector4 p1, float color1, float color2, float color3)
{
	int x, y;

	Vector4 tmp1 = Globals::object->toWorld.multiply(p1);
	Vector4 tmp2 = Globals::camera.getInverseMatrix().multiply(tmp1);
	Vector4 tmp3 = projection.multiply(tmp2);
	tmp3 = tmp3.dehomogenize();
	Vector4 a = viewport.multiply(tmp3);
	x = a[0];
	y = a[1];
	drawPoint(x, y, 1.0, 1.0, 1.0);
}

void Rasterizer::rasterize(int mode)
{
	if (mode == 0)
	{
		for (int i = 0; i < indices.size(); i++)
		{
			Vector4 v1 = Vector4(vertices[(indices[i]) * 3], vertices[(indices[i]) * 3 + 1], vertices[(indices[i]) * 3 + 2], 1);
			float color1 = 1;
			float color2 = 1;
			float color3 = 1;

			rasterize1Vertex(v1, color1, color2, color3);
		}
	}
	else if (mode == 1)
	{
		for (int i = 0; i < indices.size(); i += 3)
		{
			Vector4 v1 = Vector4(vertices[(indices[i]) * 3], vertices[(indices[i]) * 3 + 1], vertices[(indices[i]) * 3 + 2], 1);
			Vector4 v2 = Vector4(vertices[(indices[i + 1]) * 3], vertices[(indices[i + 1]) * 3 + 1], vertices[(indices[i + 1]) * 3 + 2], 1);
			Vector4 v3 = Vector4(vertices[(indices[i + 2]) * 3], vertices[(indices[i + 2]) * 3 + 1], vertices[(indices[i + 2]) * 3 + 2], 1);
			float color1 = cube_colors[(indices[i]) * 3];
			float color2 = cube_colors[(indices[i]) * 3 + 1];
			float color3 = cube_colors[(indices[i]) * 3 + 2];

			rasterizeVertices(v1, v2, v3, color1, color2, color3);
		}
	}

	else if (mode ==2)
	{
		for (int i = 0; i < indices.size(); i += 3)
		{
			Vector4 v1 = Vector4(vertices[(indices[i]) * 3], vertices[(indices[i]) * 3 + 1], vertices[(indices[i]) * 3 + 2], 1);
			Vector4 v2 = Vector4(vertices[(indices[i + 1]) * 3], vertices[(indices[i + 1]) * 3 + 1], vertices[(indices[i + 1]) * 3 + 2], 1);
			Vector4 v3 = Vector4(vertices[(indices[i + 2]) * 3], vertices[(indices[i + 2]) * 3 + 1], vertices[(indices[i + 2]) * 3 + 2], 1);
			float color1 = house_colors[(indices[i]) * 3];
			float color2 = house_colors[(indices[i]) * 3 + 1]; 
			float color3 = house_colors[(indices[i]) * 3 + 2];

			rasterizeVertices(v1, v2, v3, color1, color2, color3);
		}
	}
}

// Called whenever the window size changes
void Rasterizer::reshape(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
	zbuffer = new float[window_width * window_height];
	setViewport(window_width, window_height);;
	setProjection();
}

void Rasterizer::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
}