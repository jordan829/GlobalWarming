#ifndef _GEOTERRAIN_H_
#define _GEOTERRAIN_H_

#include "Geode.h"
#include "Matrix4.h"
#include "Vector3.h"

using namespace std;

class GeoTerrain : public Geode
{
public:
	void render(Matrix4);
};

#endif