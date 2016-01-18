#ifndef CSE167_Rasterizer_h
#define CSE167_Rasterizer_h

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Drawable.h"
#include "OBJObject.h"

using namespace std;

static int numVert;
static int numIndex;
static vector<float> vertices;
static vector<float> colors;
static vector<int> indices;
static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static float* zbuffer = new float[window_width * window_height];


class Rasterizer
{
public:
	Rasterizer(void);
	void loadData();
	void loadCube();
	void loadHouse();
	void loadObj(OBJObject obj);
	void clearBuffer();
	void initialize_zbuffer(void);
	void update_zbuffer(int x, int y, float c1, float c2, float c3, float z);
	void drawPoint(int x, int y, float r, float g, float b);
	void rasterizeTriangle(Vector4 v1, Vector4 v2, Vector4 v3, float c1, float c2, float c3);
	void rasterizeVertices(Vector4 p1, Vector4 p2, Vector4 p3, float color1, float color2, float color3);
	void rasterize1Vertex(Vector4 p1, float color1, float color2, float color3);
	void rasterize(int mode);
	void reshape(int new_width, int new_height);
	void display();
	void setViewport(int w, int h);
	void setProjection();
};

// Cube data
static float cube_vertices[] = {
	// Draw front face:
	-5.0, 5.0, 5.0,
	5.0, 5.0, 5.0,
	5.0, -5.0, 5.0,
	-5.0, -5.0, 5.0,

	// Draw left side:
	-5.0, 5.0, 5.0,
	-5.0, 5.0, -5.0,
	-5.0, -5.0, -5.0,
	-5.0, -5.0, 5.0,

	// Draw right side:
	5.0, 5.0, 5.0,
	5.0, 5.0, -5.0,
	5.0, -5.0, -5.0,
	5.0, -5.0, 5.0,

	// Draw back face:
	-5.0, 5.0, -5.0,
	5.0, 5.0, -5.0,
	5.0, -5.0, -5.0,
	-5.0, -5.0, -5.0,

	// Draw top side:
	-5.0, 5.0, 5.0,
	5.0, 5.0, 5.0,
	5.0, 5.0, -5.0,
	-5.0, 5.0, -5.0,

	// Draw bottom side:
	-5.0, -5.0, -5.0,
	5.0, -5.0, -5.0,
	5.0, -5.0, 5.0,
	-5.0, -5.0, 5.0 };

static float cube_colors[] = {
	// Draw front face:
	1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1,

	// Draw left side:
	1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1,

	// Draw right side:
	0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1,

	// Draw back face:
	1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0,

	// Draw top side:
	1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1,

	// Draw bottom side:
	0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1 };

static int cube_indices[] = {
	// Draw front face:
	0, 1, 3, 1, 2, 3,

	//Draw left side:
	4, 5, 7, 5, 6, 7,

	//Draw right side:
	8, 9, 11, 9, 10, 11,

	//Draw back face:
	12, 13, 15, 13, 14, 15,

	//Draw top side:
	16, 17, 19, 17, 18, 19,

	//Draw bottom side:
	20, 21, 23, 21, 22, 23 };

static float house_vertices[] = {
	-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
	-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
	4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
	4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
	4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
	-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face

	-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
	-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
	4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
	-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
	4, 4, -4, -4, 4, -4, 0, 8, -4 };                   // rear attic wall

// These are the RGB colors corresponding to the vertices, in the same order
static float house_colors[] = {
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // front is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // left is green
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // back is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // right is green
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // top is blue
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // bottom is blue

	0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, // grass is dark green
	0, 0, 1, 0, 0, 1, 0, 0, 1,                // front attic wall is blue
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,         // left slope is green
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,         // right slope is red
	0, 0, 1, 0, 0, 1, 0, 0, 1, };              // rear attic wall is red

// The index data stores the connectivity of the triangles; 
// index 0 refers to the first triangle defined above
static int house_indices[] = {
	0, 2, 3, 0, 1, 2,      // front face
	4, 6, 7, 4, 5, 6,      // left face
	8, 10, 11, 8, 9, 10,     // back face
	12, 14, 15, 12, 13, 14,   // right face
	16, 18, 19, 16, 17, 18,   // top face
	20, 22, 23, 20, 21, 22,   // bottom face

	24, 26, 27, 24, 25, 26,   // grass
	28, 29, 30,             // front attic wall
	31, 33, 34, 31, 32, 33,   // left slope
	35, 37, 38, 35, 36, 37,   // right slope
	39, 40, 41 };            // rear attic wall

#endif