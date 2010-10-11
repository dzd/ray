using namespace std;

#include <iostream>

#include "Ray_RenderableObject.hpp"

// RenderableObject
RenderableObject::RenderableObject(Color c, Geometry * g)
{
	cout << "RenderableObject constructed." << endl;
	color = c;
	// Point p = Point(0,0,36);
	// geo = new RPoint(p);
    geo = g;
}


// RPoint implementation
RPoint::RPoint(Point & p)
{
	Center = new Point(p);
}


bool RPoint::GetIntersection(Ray & r, float & distance)
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
		//i = *Center;
		//temporary return a fix distance
		distance = 1;
		return true;
	}
	return false;
}

Vector RPoint::GetNormal(Point & p)
{
// NA
}
// --

RSphere::RSphere(Point p, unsigned int r)
{
    Radius = r;
    Center = new Point(p);
}

bool RSphere::GetIntersection(Ray & r, float & distance)
{
    // float a;
    float b,c, deltabis;
    Point o = *(r.GetOrigin());
    Vector d = *(r.GetVector());
    Vector tmp = o - *Center;

    // a = dot(d, d); // d is a unit vector no need to calculate a
    b = dot(tmp , d); // the '2' factor is removed for the final simplification
    c = dot(tmp, tmp) - (Radius * Radius);

    deltabis = b * b - c;

    if (deltabis >  0)
    {
        // on retourne la distance
         distance = - b - sqrt(deltabis);
        return true;
    }
    else
        return false;
}

Vector RSphere::GetNormal(Point & p)
{
    return Vector(0,0,1);
}



