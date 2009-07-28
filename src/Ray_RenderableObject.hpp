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
	virtual bool GetIntersection(Ray & r, Point & i);
	
	virtual vector<float> GetNormal();
};

/**
* The point class is a the simpliest geometry
*/
class RPoint : public Geometry
{
private:
	int x, y, z;
	
public:
	RPoint(int x, int y, int z) {this->x = x; this->y = y; this->z = z;}

	bool GetIntersection(Ray & r, Point & i);
	vector<float> GetNormal();
};

class Sphere : public Geometry
{};

class Cube : public Geometry
{};

#endif //_RAY_RENDERABLE_OBJ_
