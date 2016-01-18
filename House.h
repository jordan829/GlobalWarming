#ifndef CSE167_House_h
#define CSE167_House_h

#include "Drawable.h"
#include "Rasterizer.h"

class House : public Drawable
{

public:

	float size;

	House(void);
	virtual ~House(void);

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);
	virtual void myDraw(DrawData&);

	void spin(float);

	// This data structure defines a simple house

	int nVerts = 42;    // your vertex array needs to have this many entries
	const static int v_size = 126;
	const static int c_size = 126;
	const static int i_size = 60;
};

#endif
