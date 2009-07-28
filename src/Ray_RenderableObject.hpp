#ifndef _RAY_RENDERABLE_OBJ_
#define _RAY_RENDERABLE_OBJ_

#include <vector>

class Geometry;
class LightProperty;
class Point;
class Vector;


/*Global ressources*/
float operator*(Vector& v1, Vector &v2);
Vector cross(Vector& v1, Vector &v2);



class Point
{
private:
	float x, y, z;
public:
	Point(float x, float y, float z) {this->x=x; this->y=y; this->z=z;}
	Point(const Point & p) {x=p.x; y=p.y; z=p.z;}

	float X() {return x;}
	float Y() {return y;}
	float Z() {return z;}
};



class Vector
{
private:
	float	x, y, z;

public:
	Vector(float x, float y, float z) {this->x=x; this->y=y; this->z=z;}
	Vector(Point p1, Point p2);

	Vector(const Vector& v) {x=v.x; y=v.y; z=v.z;}
	float X() {return x;}
	float Y() {return y;}
	float Z() {return z;}
};

class Ray
{
private:
	Vector *v;
	Point  *o;
public:
	Ray(Vector & v, Point & o);

	Vector GetVector() { return *v; }
	Point GetOrigin() { return *o; }
};

/**
 * Base class for renderable objects
 */
class RenderableObject
{
protected:
	bool 			isVisible;
	Geometry 		*geo;
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
	Geometry();
	
	// TODO: check if passing by value is the best choice...
	virtual bool GetIntersection(Ray & r, Point & i) = 0;
	virtual Vector GetNormal(Point & p) = 0;
};

/**
* The point class is a the simpliest geometry
*/
class RPoint : public Geometry
{
private:
	Point * p;
	
public:
	RPoint(Point & p) {this->p = new Point(p);}

	bool GetIntersection(Ray & r, Point & i);
	Vector GetNormal(Point & p);
};

class Sphere : public Geometry
{};

class Cube : public Geometry
{};

#endif //_RAY_RENDERABLE_OBJ_
