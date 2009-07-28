using namespace std;

#include "Ray_RenderableObject.hpp"


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

// RPoint implementation
bool RPoint::GetIntersection(Ray & r, Point & i)
{
// Create a vector using ray origin and current point
	Vector * p_v1 = new Vector(r.GetVector());
	Vector * p_v2 = new Vector(r.GetOrigin(), *p);
// cross product ray vector and created vector
	//p_v = cross(r.GetVector(),*p_v);
	*p_v1 = cross(*p_v1,*p_v2);
//if result is null the ray intersect the point
	if ( p_v1->X() == 0 && p_v1->Y() == 0 && p_v1->Z() == 0)
	{	
		i = *p;
		return true;
	}
	return false;
}

Vector RPoint::GetNormal(Point & p)
{
// NA
}
// --
