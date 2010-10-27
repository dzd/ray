#ifndef _RAY_MATH_
#define _RAY_MATH_

#include <iostream>

class Point
{
protected:
	float x, y, z;

public:
	Point(float x, float y, float z) {this->x=x; this->y=y; this->z=z;}
	Point(const Point & p) {x=p.x; y=p.y; z=p.z;}

//TODO: remove non const call of those getter
	float X() {return x;}
	float Y() {return y;}
	float Z() {return z;}

    float X() const {return x;}
    float Y() const {return y;}
    float Z() const {return z;}

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

	float X() const {return x;}
	float Y() const {return y;}
	float Z() const {return z;}

};


class Ray
{
private:
    Vector *v;
    Point  *o;
public:
    Ray(Vector & v, Point & o);
    Ray(const Vector & v, const Point & o);

    Vector * GetVector() { return v; }
    Point * GetOrigin() { return o; }
};

/*Global ressources*/
float operator*(Vector& v1, Vector &v2);
Vector operator*(float f, Vector &v);
Vector operator-(Point & p1, Point & p2);

Vector cross(const Vector& v1, const Vector &v2);
float dot(const Vector& v1, const Vector &v2);

ostream & operator<<(ostream &o, Point  & p);
ostream & operator<<(ostream &o, Vector & v);
ostream & operator<<(ostream &o, Ray & r);

#endif //_RAY_MATH_
