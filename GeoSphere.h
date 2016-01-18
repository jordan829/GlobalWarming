#ifndef _GEOSPHERE_H_
#define _GEOSPHERE_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class GeoSphere : public Geode 
{
public:
	void render(Matrix4);
};

#endif