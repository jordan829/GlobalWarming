#include "Globals.h"

//Camera Globals::camera = Camera();
Camera Globals::camera;

//Cube Globals::cube = Cube(10.0);
Cube Globals::cube(10.0);

Texture Globals::ft;
Texture Globals::bk;
Texture Globals::lf;
Texture Globals::rt;
Texture Globals::up;
Texture Globals::dn;
Texture Globals::trooper;
Texture Globals::chestplate;
Texture Globals::terrain;
////////////////////////////////////
vector<vector<Vector3>> Globals::verts(1024, vector<Vector3>(1024));
vector<vector<Vector3>> Globals::norms(1024, vector<Vector3>(1024));
bool Globals::recalcNorms = false;

bool Globals::drawChest = true;

//Light Globals::light = Light();
Light Globals::light;
Light Globals::directional= Light();
Light Globals::point = Light();
Light Globals::spot = Light();
Light* Globals::currentLight;

Shader* Globals::shader = NULL;
float Globals::currWater = 0;

Sphere Globals::sphere = Sphere(5, 50, 50);
Cone Globals::cone(0.3, 1.0, 25, 25);
Drawable* Globals::lightShape;

bool Globals::light_selected = false;
int Globals::light_id;

Rasterizer* Globals::rasterizer = new Rasterizer();
bool Globals::drawPoints = true;
float Globals::elevationScale = 1.0;
float Globals::maxHeight = 0;

/* House object */
//House Globals::house = House();

/* OBJObjects */
OBJObject Globals::bunny = OBJObject();
OBJObject Globals::dragon = OBJObject();
OBJObject Globals::bear = OBJObject();
/**************/

Drawable* Globals::object;

//DrawData Globals::drawData = DrawData();
//UpdateData Globals::updateData = UpdateData();
DrawData Globals::drawData;
UpdateData Globals::updateData;

bool Globals::zbuf = 0;
bool Globals::interp = 0;