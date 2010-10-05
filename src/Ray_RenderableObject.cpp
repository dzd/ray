using namespace std;

#include <iostream>

#include "Ray_RenderableObject.hpp"

// RenderableObject
RenderableObject::RenderableObject(Color c)
{
	cout << "RenderableObject constructed." << endl;
	color = c;
	Point p = Point(0,0,36);
	geo = new RPoint(p);
}


// RPoint implementation
RPoint::RPoint(Point & p)
{
	Center = new Point(p);
}


bool RPoint::GetIntersection(Ray & r, Point & i)
{
// Create a vector using ray origin and current point
	Vector * p_v1 = new Vector(*(r.GetVector()));
	Vector * p_v2 = new Vector(*(r.GetOrigin()), *Center);

// cross product ray vector and created vector
	//p_v = cross(r.GetVector(),*p_v);
	*p_v1 = cross(*p_v1,*p_v2);
//if result is null the ray intersect the point
	if ( p_v1->X() == 0 && p_v1->Y() == 0 && p_v1->Z() == 0)
	{	
		i = *Center;
		return true;
	}
	return false;
}

Vector RPoint::GetNormal(Point & p)
{
// NA
}
// --

RSphere::RSphere(Point &p, unsigned int r)
{
    Radius = r;
    Center = new Point(p);
}

bool RSphere::GetIntersection(Ray & r, Point & i)
{

}


