#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "House.h"
#include "OBJObject.h"
#include "Rasterizer.h"
#include "Sphere.h"
#include "Cone.h"
#include "Skybox.h"
#include "Texture.h"
#include "Shader.h"

#define PI 3.14159265

#define DIRECTIONAL 1
#define POINT 2
#define SPOT 3
#define GRID_DIMENSION 1024
#define TERRAIN_PIECES 2
#define ELEVATION_SCALE 0.2
#define WATER_SCALE 5
#define TERRAIN 0
#define SUN 1
#define SUN_MAX  185


class Globals
{
    
public:
    
    static Camera camera;

    static Cube cube;

	static Texture ft;
	static Texture bk;
	static Texture lf;
	static Texture rt;
	static Texture up;
	static Texture dn;
	static Texture trooper;
	static Texture chestplate;
	static Texture terrain;
	////////////////////////////////////
	static vector<vector<Vector3>> verts;
	static vector<vector<Vector3>> norms;
	static bool drawPoints;
	static bool recalcNorms;
	static float elevationScale;
	static float maxHeight;
	static Shader* shader;
	static float currWater;

	static bool drawChest;

    static Light light;
	static Light directional;
	static Light point;
	static Light spot;

	static Light* currentLight;

	static bool light_selected;
	static int light_id;

	static Sphere sphere;
	static Cone cone;
	static Drawable* lightShape;

    static DrawData drawData;
    static UpdateData updateData;

	static House house;

	static OBJObject bunny;
	static OBJObject dragon;
	static OBJObject bear;

	static Drawable* object;

	static Rasterizer* rasterizer;

	static bool zbuf;
	static bool interp;
};

#endif
