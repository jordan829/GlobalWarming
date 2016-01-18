#include <iostream>
using namespace std;
#include "glee.h"
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Skybox.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Rasterizer.h"
#include "MatrixTransform.h"
#include "GeoSphere.h"
#include "GeoCube.h"
#include "GeoChest.h"
#include "GeoBall.h"
#include "GeoTerrain.h"

int Window::width  = 1600;   //Set window width in pixels here
int Window::height = 900;   //Set window height in pixels here

bool leftClick = false;
bool rightClick = false;
bool zoom = false;
int mouseX = 0;
int mouseY = 0;

Vector3 lastPoint;
bool draw_sky = 1;

//////////////////////////////////////////////////////////////////////////////////////////////

//vector<MatrixTransform*> scene(TERRAIN_PIECES);

Matrix4 meh;	//Used for grid translation / scaling
Matrix4 bleh;	//Used for grid rotation

Skybox skybox(0);

float sunx = 125;
float suny = 0;
float sunz = 136;

bool east = 1;
bool west = 0;

Color sunColor = Color::yellow();

//////////////////////////////////////////////////////////////////////////////////////////////

void Window::initialize(void)
{
	meh.identity();
	bleh.identity();

	Globals::shader = new Shader("diffuse_only.vert", "diffuse_only.frag", true);

	//Default light
	/*Vector4 lightPos(10.0, 50.0, -10.0, 1.0);
	Globals::light.position = lightPos;
	Globals::light.quadraticAttenuation = 0.0005;
*/
	////Point light
	Globals::point.quadraticAttenuation = 0.000005;
	Globals::point.diffuseColor = sunColor;
	Globals::point.specularColor = sunColor;
	//Globals::point.ambientColor = sunColor;
	

	glEnable(GL_NORMALIZE);

	//////////// Set camera position /////////////
	Vector3 e, d, u;
	e.set(0.0, 75.0, 250.0);
	d.set(20.0, 35.0, 10.0);
	u.set(0.0, 1.0, 0.0);
	Globals::camera.set(e, d, u);
	Globals::camera.update();
	//////////////////////////////////////////////

	//Initialize skybox
	skybox = Skybox(999.0);

	/* * * * * * * * * * *
	*   Create Textures  *
	*					 *
	*	Texture options: *
	*	  darkskies		 *
	*	  purplenebula   *
	*	  arctic		 *
	*	  iceflats		 *
	*	  tatooine		 *
	* * * * * * * * * * */
	Globals::ft = Texture("purplenebula_ft.ppm");	//Front face
	Globals::bk = Texture("purplenebula_bk.ppm");	//Back face
	Globals::lf = Texture("purplenebula_lf.ppm");	//Left face
	Globals::rt = Texture("purplenebula_rt.ppm");	//Right face
	Globals::up = Texture("purplenebula_up.ppm");	//Top face
	Globals::dn = Texture("purplenebula_dn.ppm");	//Bottom face

	//Initialize terrain texture
	Globals::terrain = Texture("SanDiegoTerrain.ppm");

	//Generate terrain vertex coordinates
	generateTerrainVerts();

	calculateNorms();
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
	//Globals::light.bind(0);
	Globals::point.bind(0);

	//Draw skybox
	if (!draw_sky)
	{
		// Draw skybox faces
		skybox.draw_ft(Globals::drawData);
		skybox.draw_bk(Globals::drawData);
		skybox.draw_lf(Globals::drawData);
		skybox.draw_rt(Globals::drawData);
		skybox.draw_up(Globals::drawData);
		skybox.draw_dn(Globals::drawData);
	}

	//Draw terrain / sun
	drawScene();

	//Calculate next position for sun. Travels on a parabolic path. Also determines sun color
	calculateSunPath();

    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}

void Window::generateTerrainVerts()
{
	for (int x = 0; x < GRID_DIMENSION; x++)
	{
		for (int y = 0; y < GRID_DIMENSION; y++)
		{
			Globals::verts[x][y][0] = x;	
			Globals::verts[x][y][1] = Globals::terrain.tdata[(x * GRID_DIMENSION + y) * 3];
			Globals::verts[x][y][2] = y;

			if (Globals::verts[x][y][1] > Globals::maxHeight)
				Globals::maxHeight = Globals::verts[x][y][1] / 4;
		}
	}
}

void Window::calculateNorms()
{
	for (float y = 0; y < GRID_DIMENSION - 1; y++)
	{
		float x0, y0, z0;
		float x1, y1, z1;
		float x2, y2, z2;
		float c0, c1;
		Vector3 v0, v1, v2;
		Vector3 norm;

		//Traverse row left to right
		for (float x = 0; x < GRID_DIMENSION; x++)
		{
			x0 = -(x - 512) / 4;
			y0 = ((Globals::verts[x][y + 1][1]) / 4) * Globals::elevationScale;
			z0 = -(y + 1 - 512) / 4;

			x1 = -(x - 512) / 4;
			y1 = ((Globals::verts[x][y][1]) / 4) * Globals::elevationScale;
			z1 = -(y - 512) / 4;

			//Dont calculate next vertex if out of bounds
			if (x < GRID_DIMENSION - 1)
			{
				x2 = -(x + 1 - 512) / 4;
				y2 = ((Globals::verts[x + 1][y + 1][1]) / 4) * Globals::elevationScale;
				z2 = -(y + 1 - 512) / 4;
			}

			v0 = Vector3(x0, y0, z0);
			v1 = Vector3(x1, y1, z1);
			v2 = Vector3(x2, y2, z2);

			norm = (v0 - v1).cross(v2 - v1); //Vertex normal
			norm = norm.normalize();
			Globals::norms[x][y] = norm;
		}
	}
}

void Window::calculateSunPath()
{
	//Determine sun direction
	if (sunz == -136)
	{
		west = true;
		east = false;
	}

	else if (sunz == 136)
	{
		west = false;
		east = true;
	}

	//Move sun along determined direction
	if (west)
		sunz += 4.0;

	else if (east)
		sunz -= 4.0;

	//Calculate and set sun height
	suny = -((sunz * sunz) / 100) + 185;

	//Change sun color. White at apex, yellow at lowest points
	Globals::point.diffuseColor = Color(1, 1, suny / SUN_MAX);
	Globals::point.specularColor = Color(1, 1, suny / SUN_MAX);
	//Globals::point.ambientColor = Color(1, 1, suny / SUN_MAX);
}

void Window::drawScene()
{
	glMatrixMode(GL_MODELVIEW);

	Matrix4 identity;
	Matrix4 translate;
	Matrix4 rotate, scale, trans;
	Vector3 axis;
	MatrixTransform scene, sun;
	float x, y;

	//Init
	identity.identity();
	//terrain = MatrixTransform(identity);
	sun = MatrixTransform(identity);
	scene = MatrixTransform(identity);

	// Generate terrain node 
	scene.addChild(&GeoTerrain());
	//terrain.addChild(&GeoTerrain());

	// Generate sun node
	trans.makeTranslate(sunx, suny, sunz);
	sun.setTransformationMatrix(trans * sun.getTransformationMatrix());
	sun.addChild(&GeoSphere()); 

	//Add pieces to scene
	//terrain.addChild(&terrain);
	//sun.addChild(&sun);

	//scene.addChild(&terrain);
	scene.addChild(&sun);

	//Apply rotations / translations
	translate.identity();
	scene.setTransformationMatrix(translate);
	scene.setTransformationMatrix(bleh * scene.getTransformationMatrix());
	scene.setTransformationMatrix(meh * scene.getTransformationMatrix());

	//Draw scene
	scene.draw(identity);

	//Set light to same position as sphere
	Matrix4 pos = sun.getTransformationMatrix();
	pos = bleh * pos;
	pos = meh * pos;
	Vector4 p = pos * Vector4(1, 1, 1, 1);
	p.toVector3();
	Globals::point.position = Vector4(p[0], p[1], p[2], 1);
}

void Window::keyCallback(unsigned char key, int x, int y)
{
	Matrix4 xTrans, yTrans, zTrans;	// Translation matrices
	Matrix4 scale;					// Scaling matrix
	Matrix4 rotate;					// Rotation matrix
	Vector3 z;

	switch (key)
	{
		// 'x' : Move left
	case 'x':
		xTrans.makeTranslate(-1.2, 0, 0);
		meh = xTrans * meh;
		break;

		// 'X' : Move right
	case 'X':
		xTrans.makeTranslate(1.2, 0, 0);
		meh = xTrans * meh;
		break;

		// 'y' : Move down
	case 'y':
		yTrans.makeTranslate(0, -1.2, 0);
		meh = yTrans * meh;
		break;

		// 'Y' : Move up
	case 'Y':
		yTrans.makeTranslate(0, 1.2, 0);
		meh = yTrans * meh;
		break;

		// 'z' : Move in
	case 'z':
		zTrans.makeTranslate(0, 0, -1.2);
		meh = zTrans * meh;
		break;

		// 'Z' : Move out
	case 'Z':
		zTrans.makeTranslate(0, 0, 1.2);
		meh = zTrans * meh;
		break;

		// 'r' : Reset
	case 'r':
		meh.identity();
		bleh.identity();
		Globals::elevationScale = 1.0;
		Globals::currWater = 0;
		calculateNorms();
		break;

		// 'o' : Orbit clockwise
	case 'o':
		z.set(0, 0, 1);
		rotate.makeRotateArbitrary(z, -.16);
		bleh = bleh * rotate;
		break;

		// 'O' : Orbit counterclockwise
	case 'O':
		z.set(0, 0, 1);
		rotate.makeRotateArbitrary(z, .16);
		bleh = bleh * rotate;
		break;

		// 's' : Scale down
	case 's':
		scale.makeScale(0.95, 0.95, 0.95);
		meh = scale * meh;
		break;

		// 'S' : Scale up
	case 'S':
		scale.makeScale(1.05, 1.05, 1.05);
		meh = scale * meh;
		break;
		
		// 'e' : Draw terrain vertices only
	case 'e':
		Globals::drawPoints = !Globals::drawPoints;
		break;

		// 'c' : Set mouse function to zoom
	case 'c':
		zoom = !zoom;
		break;

		// '0' : Toggle skybox visibility
	case '0':
		draw_sky = !draw_sky;
		break;
	}
}

void Window::mouseFunc(int key, int state, int x, int y)
{
	switch (key)	// Determine when mouse button is clicked
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			leftClick = true;
			lastPoint = trackBallMapping(Window::width, Window::height, x, y);
			mouseX = x;
			mouseY = y;
		}

		else
		{
			leftClick = false;

			if (Globals::recalcNorms)
				calculateNorms();

			Globals::recalcNorms = false;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			rightClick = true;
			lastPoint = trackBallMapping(Window::width, Window::height, x, y);
			mouseX = x;
			mouseY = y;
		}

		else
		{
			rightClick = false;

			if (Globals::recalcNorms)
				calculateNorms();

			Globals::recalcNorms = false;
		}
		break;
	}
}

void Window::mouseMotion(int x, int y)
{
	Matrix4 xyTrans, zTrans;
	Matrix4 scale, rotate;
	Vector3 axis;
	Vector3 currentPoint;
	Vector3 point;
	float rotateAngle = 0.0;

	currentPoint = trackBallMapping(Window::width, Window::height, mouseX, mouseY);

	if (leftClick)
	{
		//Exaggerate elevation
		if (mouseX < 100)
		{
			//If mouse moves up, increase scale
			if (currentPoint[1] > lastPoint[1])
				Globals::elevationScale += ELEVATION_SCALE;

			//If mouse moves down, decrease scale
			else if (currentPoint[1] < lastPoint[1])
			{
				if (Globals::elevationScale >= 0.0)
					Globals::elevationScale -= ELEVATION_SCALE;
				if (Globals::elevationScale < 0)
					Globals::elevationScale = 0;
			}

			//Update positions
			Globals::recalcNorms = true;
			lastPoint = currentPoint;
			mouseX = x;
			mouseY = y;
		}

		else if (mouseX > width - 100)
		{
			//If mouse moves up, increase scale
			if (currentPoint[1] > lastPoint[1])
				Globals::currWater += WATER_SCALE;

			//If mouse moves down, decrease scale
			else if (currentPoint[1] < lastPoint[1])
			{
				if (Globals::currWater >= 0)
					Globals::currWater -= WATER_SCALE;
				if (Globals::currWater < 0)
					Globals::currWater = 0;
			}

			//Update positions
			lastPoint = currentPoint;
			mouseX = x;
			mouseY = y;
		}
	
		else
		{
			axis = lastPoint.cross(currentPoint);
			rotateAngle = lastPoint.angle(currentPoint);
			rotate = rotate.makeRotateArbitrary(axis, rotateAngle);

			bleh = rotate * bleh;

			lastPoint = currentPoint;
			mouseX = x;
			mouseY = y;
		}
	}

	else if (rightClick)
	{
		//Exaggerate elevation
		if (mouseX < 100)
		{
			//If mouse moves up, increase scale
			if (currentPoint[1] > lastPoint[1])
				Globals::elevationScale += ELEVATION_SCALE;

			//If mouse moves down, decrease scale
			else if (currentPoint[1] < lastPoint[1])
			{
				if (Globals::elevationScale >= 0.0)
					Globals::elevationScale -= ELEVATION_SCALE;
				if (Globals::elevationScale < 0)
					Globals::elevationScale = 0;
			}

			//Update positions
			Globals::recalcNorms = true;
			lastPoint = currentPoint;
			mouseX = x;
			mouseY = y;
		}

		else if (mouseX > width - 100)
		{
			//If mouse moves up, increase scale
			if (currentPoint[1] > lastPoint[1])
				Globals::currWater += WATER_SCALE;

			//If mouse moves down, decrease scale
			else if (currentPoint[1] < lastPoint[1])
			{
				if (Globals::currWater >= 0.0)
					Globals::currWater -= WATER_SCALE;
			}

			//Update positions
			lastPoint = currentPoint;
			mouseX = x;
			mouseY = y;
		}

		else
		{
			//Translate along z axis
			if (zoom)
			{
				point = lastPoint - currentPoint;
				point = point.scale(9.0);
				zTrans.makeTranslate(0, 0, point[1]);

				meh = zTrans * meh;

				lastPoint = currentPoint;
				mouseX = x;
				mouseY = y;
			}

			//Translate along x / y axis
			else
			{
				point = currentPoint - lastPoint;
				point = point.scale(50.0);
				xyTrans.makeTranslate(point[0], point[1], 0);

				meh = xyTrans * meh;

				lastPoint = currentPoint;
				mouseX = x;
				mouseY = y;
			}
		}
	}
}

Vector3 Window::trackBallMapping(int width, int height, int mouseX, int mouseY)
{
	Vector3 v;
	float d;
	v[0] = (2.0 * mouseX - width) / width;
	v[1] = (height - 2.0 * mouseY) / height;
	v[2] = 0.0;
	d = sqrtf(v[0] * v[0] + v[1] * v[1]);
	d = (d<1.0) ? d : 1.0;
	v[2] = sqrtf(1.001 - d*d);
	return v.normalize();
}