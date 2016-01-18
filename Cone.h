#ifndef CSE167_Cone_h
#define CSE167_Cone_h

#include <iostream>
#include "Drawable.h"

class Cone : public Drawable
{

public:

	double base, height;
	int slices, stacks;

	Cone(double, double, int, int);

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

};

#endif
