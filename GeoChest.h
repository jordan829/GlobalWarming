#ifndef _GEOCHEST_H_
#define _GEOCHEST_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class GeoChest : public Geode
{
public:
	void render(Matrix4);
};

#endif