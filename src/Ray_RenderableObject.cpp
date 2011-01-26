using namespace std;
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

//---- RPoint ------------------------------------------------------------------------
RPoint::RPoint(Point & p)
{
	Center = new Point(p);
}


bool RPoint::GetIntersection(const Ray & r, float & distance)
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

//---- RSphere ------------------------------------------------------------------
map<string, string> RSphere::mandatoryAttributes;
bool RSphere::mandatoryAttributesFilled = false;

/**
 * RSphere constructor
 */
RSphere::RSphere(Point p, unsigned int r)
{
    Radius = r;
    Center = new Point(p);
}

/**
 * RSphere ray's intersection computation
 */
bool RSphere::GetIntersection(const Ray & r, float & distance)
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

/**
 * RSphere normal at one point computation.
 */
Vector RSphere::GetNormal(Point & p)
{
    return Vector(*Center, p);
}

/**
 * Get the list of mandatory of attributes to construct objects of the scene.
 */
map<string, string> & RSphere::GetMandatoryAttributes()
{

    if( ! mandatoryAttributesFilled )
    {
        mandatoryAttributes["radius"]   = "";
        mandatoryAttributes["position"] = "";
        mandatoryAttributesFilled = true;
    }

    return mandatoryAttributes;
}


//----- RPlan ------------------------------------------------------------------------

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
    VN = new Vector(cross(*OB, *OA));

    cout << "OA: " << *OA << endl;
    cout << "OB: " << *OB << endl;
    cout << "VN: " << *VN << endl;
}

bool RPlan::GetIntersection(const Ray & r, float & distance)
{
    Vector * r_vector = r.GetVector();

    if ( dot(*r_vector, *VN) > 0.9 )
        return false;
    
    Matrix3 m1, m2;
    m1.setAt(1,1, r_vector->X());
    m1.setAt(1,2, OA->X());
    m1.setAt(1,3, OB->X());

    m1.setAt(2,1, r_vector->Y());
    m1.setAt(2,2, OA->Y());
    m1.setAt(2,3, OB->Y());

    m1.setAt(3,1, r_vector->Z());
    m1.setAt(3,2, OA->Z());
    m1.setAt(3,3, OB->Z());

    //cout << m1.det() << endl;

    if (! m1.inverse(m2) )
        return false;

    Vector v1(r.GetOrigin()->X() - O->X(),
              r.GetOrigin()->Y() - O->Y(),
              r.GetOrigin()->Z() - O->Z());

    Vector v_res = m2 * v1;

    distance =-v_res.X();
    u        = v_res.Y();
    v        = v_res.Z();
    //cout << "u: " << u << ",v: "<< v << endl;
    return true;
}

Vector RPlan::GetNormal(Point & p)
{
    return *VN;
}

//----- RTriangle ------------------------------------------------------------------------
RTriangle::RTriangle(Point O, Point A, Point B, float u, float v) : RPlan(O, A, B)
{
    this->coord_u = u;
    this->coord_v = v;
}

bool RTriangle::GetIntersection(const Ray & r, float & distance)
{
    if ( RPlan::GetIntersection(r, distance) )
    {
        if(RPlan::u < coord_u && RPlan::v < coord_v)
            return true;
    }
    return false;
}

