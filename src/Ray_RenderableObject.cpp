using namespace std;

#include <iostream>

#include "Ray_RenderableObject.hpp"

//---- RenderableObject
// init of static RenderableObject properties
int RenderableObject::id = 0;

RenderableObject::RenderableObject(Color c, Geometry * g)
{
    SetId();
    cout << "RenderableObject constructed, id: "<< object_id << endl;
    color = c;
    geo = g;
}


//---- RPoint
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
    return Vector(0,0,0);
}


RSphere::RSphere(Point p, unsigned int r)
{
    Radius = r;
    Center = new Point(p);
}

bool RSphere::GetIntersection(Ray & r, float & distance)
{
    // float a;
    double b,c, deltabis;
    double s1,s2;


    Point o = *(r.GetOrigin());
    Vector d = *(r.GetVector());
    Vector tmp = o - *Center;

    // a = dot(d, d); // d is a unit vector no need to calculate a
    b = dot(tmp , d); // the '2' factor is removed for the final simplification
    c = dot(tmp, tmp) - (Radius * Radius);

    deltabis = b * b - c;

    if (deltabis <  0)
    {
        return false;
    }

    // on retourne la distance
    s1 = - b - sqrt(deltabis);
    s2 = - b + sqrt(deltabis);

    if(s1 > 0.1)// and s1 < s2 )
    {
        distance = s1;
        return true;
    }
    if(s2 > 0.1)
    {
        distance = s2;
        return true;
    }
    return false;
}

Vector RSphere::GetNormal(Point & p)
{
    return Vector(*Center, p);
}

//----- RPlan

/*
 * Constructor with a point and a normal vector
 */
// RPlan::RPlan(const Point o, const Vector vnormal)
// {
//     origin = new Point(o);
//     this->vnormal = new Vector(vnormal);
// }
/*
 * Constructor with 3 points
 * It assumes O,A,B distinct and all on the same line.
 */
RPlan::RPlan(Point O, Point A, Point B)
{
    this->O = new Point(O);
    this->A = new Point(A);
    this->B = new Point(B);

    OA = new Vector(O, A);
    OB = new Vector(O, B);

    //VN = new Vector();

}

bool RPlan::GetIntersection(Ray & r, float & distance)
{
    float a1, a2, a3, b1, b2, b3;

    float xr = r.GetVector()->X();
    float yr = r.GetVector()->Y();
    float zr = r.GetVector()->Z();
    float xo = r.GetOrigin()->X();
    float yo = r.GetOrigin()->Y();
    float zo = r.GetOrigin()->Z();

    if ( xr == 0 ) { return false;}

    a1 = yr * (xo     - O->X()) - xr * (yo     - O->Y());
    a2 = yr * (A->X() - O->X()) + xr * (A->Y() - O->Y());
    a3 =-xr * (B->Y() - O->Y()) + yr * (B->X() - O->X());

    b1 = zr * (xo     - O->X()) - xr * (zo     - O->Z());
    b2 = zr * (A->X() - O->X()) + xr * (A->Z() - O->Z());
    b3 =-xr * (B->Z() - O->Z()) + zr * (B->X() - O->X());

    float alpha = (b3 * a1 - a3 * b1) / (b3 * a2 + a3 * b2);
    float beta  = (a1 - alpha * a2) / a3;

    float t = ((xo - O->X()) - alpha * (A->X() - O->X()) - beta * (B->X() - O->X())) / xr;

    distance = t;
    return true;
}


Vector RPlan::GetNormal(Point & p)
{
    return Vector(1,1,1);
}


