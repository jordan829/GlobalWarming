#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Rasterizer.h"
#include "Globals.h"

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; // window size
	//static float* pixels;
	static float angle;
	static float angle_bunny;
	static float angle_dragon;
	static float angle_bear;
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyCallback(unsigned char, int, int);
	static void specialFunc(int key, int x, int y);
	static void mouseFunc(int key, int state, int x, int y);
	static void mouseMotion(int x, int y);
	static void printPos(void);
	static Vector3 trackBallMapping(int width, int height, int mouseX, int mouseY);
	static void drawTroops();
	static void calculateAnimation();
	static void generateTerrainVerts();
	static void drawScene();    
	static void calculateSunPath();
	static void calculateNorms();
};

#endif

