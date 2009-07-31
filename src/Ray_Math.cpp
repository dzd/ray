using namespace std;

#include "Ray_Math.hpp"

/**
* Operator * for dot product between two vectors
*/
float operator*(Vector& v1, Vector &v2)
{
	return v1.X()*v2.X() + v1.Y()*v2.Y() + v1.Z()*v2.Z();
}

Vector operator-(Point & p1, Point & p2)
{
	return Vector(p1.X() - p2.X(),
				  p1.Y() - p2.Y(),
				  p1.Z() - p2.Z());
}

/**
* Cross product
*/
Vector cross(Vector& v1, Vector &v2)
{
	return Vector(v1.Y()*v2.Z()-v2.Y()*v1.Z(),
				  v1.Z()*v2.X()-v2.Z()*v1.X(),
 				  v1.X()*v2.Y()-v2.X()*v1.Y());
}

Ray::Ray(Vector & v, Point & o)
{ 
	this->v = new Vector(v);
	this->o = new Point(o);
}

Vector::Vector(Point p1, Point p2)
{
	Vector v = p2 - p1;
	x = v.X();
	y = v.Y();
	z = v.Z();
}

ostream & operator<<(ostream &o, Point  & p) { return o << "(" << p.X() << "," << p.Y() << "," << p.Z() << ")"; }
ostream & operator<<(ostream &o, Vector & v) { return o << "[" << v.X() << "," << v.Y() << "," << v.Z() << "]"; }

