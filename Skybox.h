#ifndef CSE167_Skybox_h
#define CSE167_Skybox_h

#include "Drawable.h"

class Skybox : public Drawable
{

public:

	float size;

	Skybox(float);
	virtual ~Skybox(void);

	//Draw functions for each face:
	void draw_ft(DrawData& data);	//Front
	void draw_bk(DrawData& data);	//Back
	void draw_lf(DrawData& data);	//Left
	void draw_rt(DrawData& data);	//Right
	void draw_up(DrawData& data);	//Top
	void draw_dn(DrawData& data);	//Bottom

	virtual void update(UpdateData&);
};

#endif

