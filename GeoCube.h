#ifndef _GEOCUBE_H_
#define _GEOCUBE_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class GeoCube : public Geode 
{
public:
	void render(Matrix4);
};

#endif