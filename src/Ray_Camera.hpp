#ifndef _RAY_Camera_
#define _RAY_Camera_

#include <list>

#include "Ray_Math.hpp"
#include "Ray_Color.hpp"

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

	int GetWidth() { return Width; }
	int GetHeight() { return Height; }

	void InitScreenIterator();
	bool GetNextRay(Ray * r);
};
/**
* This Class derives from the math Point class defined in Ray_Math.hpp
* it simply adds a color to basic points.
*/
class ScreenPoint : public Point
{
private:
	Color * c;

public:	
	ScreenPoint(float x, float y, float z) : Point(x, y, z) {c = new Color(0,0,0);}
	ScreenPoint(const Point & p) : Point(p) {}

// 	void SetColor(Color color) { *c = 
};

#endif //_RAY_Camera_
