#ifndef _RAY_Camera_
#define _RAY_Camera_

#include "Ray_Math.hpp"

/**
* The camera class
**/
class Camera
{
private:
	Point 	  *	Origin;
	Vector 	  *	Direction;
	int 		Width;
	int			Height;
	list<Point>	screen;

public:
	Camera(Point origin, Vector direction, int width, int height);

	void SetDirection(Vector & v);
	void SetTarget(Point & p);
	void SetOrigin(Point & p);
	void SetScreen(int w, int h);
	

};


#endif //_RAY_Camera_
