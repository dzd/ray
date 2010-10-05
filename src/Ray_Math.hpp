#ifndef _RAY_MATH_
#define _RAY_MATH_

#include <iostream>

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

    Vector * Normed();

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

	Vector* GetVector() { return v; }
	Point* GetOrigin() { return o; }
};

/*Global ressources*/
float operator*(Vector& v1, Vector &v2);
Vector cross(Vector& v1, Vector &v2);
ostream & operator<<(ostream &o, Point  & p);
ostream & operator<<(ostream &o, Vector & v);
ostream & operator<<(ostream &o, Ray & r);


#endif //_RAY_MATH_
