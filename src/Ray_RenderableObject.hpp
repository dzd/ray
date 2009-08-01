#ifndef _RAY_RENDERABLE_OBJ_
#define _RAY_RENDERABLE_OBJ_

#include <vector>

#include "Ray_Math.hpp"

class Geometry;
class LightProperty;
/*class Point;
class Vector;*/

/**
 * Base class for renderable objects
 */
class RenderableObject
{
protected:
	bool 			isVisible;
public:
	// temporary public for testing purpose.
	Geometry 		*geo;
private:
	LightProperty 	*lp;

public:
	RenderableObject();
	void SetVisible(bool v=true) { isVisible = v; }
};


/**
* Base class for geometry definition
*/
class Geometry
{
public:
	Geometry() {}
	
	virtual bool GetIntersection(Ray & r, Point & i) = 0;
	virtual Vector GetNormal(Point & p) = 0;
};

/**
* The point class is a the simpliest geometry
*/
class RPoint : public Geometry
{
private:
	Point * Center;
	
public:
	RPoint(Point & p);

	bool GetIntersection(Ray & r, Point & i);
	Vector GetNormal(Point & p);
};

class Sphere : public Geometry
{};

class Cube : public Geometry
{};

#endif //_RAY_RENDERABLE_OBJ_
