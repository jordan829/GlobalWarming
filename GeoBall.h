#ifndef _GEOBALL_H_
#define _GEOBALL_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class GeoBall : public Geode
{
public:
	void render(Matrix4);
};

#endif