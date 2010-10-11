#ifndef _RAY_RENDERABLE_OBJ_
#define _RAY_RENDERABLE_OBJ_

#include <math.h>

#include <vector>

#include "Ray_Math.hpp"
#include "Ray_Color.hpp"

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
	Color			color;

public:
	// temporary public for testing purpose.
	Geometry 		*geo;
private:
	LightProperty 	*lp;

public:
	RenderableObject(Color c, Geometry * g);
	void SetVisible(bool v=true) { isVisible = v; }
	Color& GetColor() {return color;}
};


/**
* Base class for geometry definition
*/
class Geometry
{
public:
	Geometry() {}
	
	virtual bool GetIntersection(Ray & r, float & distance) = 0;
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

	bool GetIntersection(Ray & r, float & distance);
	Vector GetNormal(Point & p);
};

class RSphere : public Geometry
{
private:
    Point * Center;
    unsigned int      Radius;

public:
    RSphere(Point p, unsigned int r);

    bool GetIntersection(Ray & r, float & distance);
    Vector GetNormal(Point & p);
};

class Cube : public Geometry
{};


#endif //_RAY_RENDERABLE_OBJ_
