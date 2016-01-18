#include "Camera.h"

Camera::Camera()
{
	reset();
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
	Vector3 zc = e - d;
	float zc_mag = zc.magnitude();
	zc = zc.multiply(1/zc_mag);

	Vector3 xc;
	xc = up.cross(zc);
	float xc_mag = xc.magnitude();
	xc = xc.multiply(1/xc_mag);

	Vector3 yc;
	yc = zc.cross(xc);

    //Use these axes and the e vector to create a camera matrix c
	c.set(xc[0], xc[1], xc[2], 0,
				yc[0], yc[1], yc[2], 0,
				zc[0], zc[1], zc[2], 0,
				e[0], e[1], e[2], 1);

    //Use c to solve for an inverse camera matrix ci
	Matrix4 R;
	Matrix4 Ri;
	Matrix4 Ti;
	R.set(xc[0], xc[1], xc[2], 0,
		  yc[0], yc[1], yc[2], 0,
		  zc[0], zc[1], zc[2], 0,
		  0, 0, 0, 1);

	Ri = R.transpose();

	Ti.set(1, 0, 0, 0,
		  0, 1, 0, 0,
		  0, 0, 1, 0,
		 -e[0], -e[1], -e[2], 1);

	ci = Ri * Ti;
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}

void Camera::reset()
{
	c.identity();
	e.set(0.0, 0.0, 20.0);
	d.set(0.0, 0.0, 0.0);
	up.set(0.0, 1.0, 0.0);

	//Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
	//This is used as a default camera position for Project 1
	c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
	ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}
