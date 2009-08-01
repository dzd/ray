#ifndef _RAY_Camera_
#define _RAY_Camera_

#include <list>

#include "Ray_Math.hpp"

/**
* The camera class
**/
class Camera
{
private:
	Point 	  *	Center;
	Vector 	  *	Direction;
	int 		Width;
	int			Height;
	list<Point>	Screen;
	list<Point>::iterator it;

	void InitDefaultScreen();

public:
	Camera(Point center, Vector direction, int width=640, int height=480);

	void SetDirection(Vector & v);
	void SetTarget(Point & p);
	void SetCenter(Point & p);
	void SetScreen(int w, int h);

	void InitScreenIterator();
	bool GetNextRay(Ray * r);
	

};


#endif //_RAY_Camera_
