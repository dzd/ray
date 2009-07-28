using namespace std;

#include "Ray_RenderableObject.hpp"


/**
* Operator * for dot product between two vectors
*/
float operator*(Vector& v1, Vector &v2)
{
	return v1.X()*v2.X() + v1.Y()*v2.Y() + v1.Z()*v2.Z();
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



bool RPoint::GetIntersection(Ray & r, Point & i)
{
	
}


