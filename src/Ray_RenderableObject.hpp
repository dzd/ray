#ifndef _RAY_RENDERABLE_OBJ_
#define _RAY_RENDERABLE_OBJ_

#include <iostream>

#include <cmath>

#include <map>

#include "Ray_Math.hpp"
#include "Ray_Color.hpp"

class Geometry;
class LightProperty;
/*class Point;
class Vector;*/

/**
 * Base class for renderable objects
 */
class RenderableObject
{
protected:
    bool        isVisible;
    Color       color;

    int         object_id;

    static int  id;
public:
    // temporary public for testing purpose.
    Geometry    *geo;
private:
    LightProperty   *lp;
    void SetId() { id++; object_id = id;}

public:
    RenderableObject(Color c, Geometry * g);
    void SetVisible(bool v=true)    { isVisible = v;}
    Color GetColor()                {return color;}

    int GetId() {return object_id;}
};


/**
* Base class for geometry definition
*/
class Geometry
{
public:
    Geometry() {}

    virtual bool GetIntersection(const Ray & r, float & distance) = 0;
    virtual Vector GetNormal(Point & p) = 0;

    //static list< set<string> > GetMandatoryAttributes() {}
};

/**
* The point class is a the simpliest geometry
*/
class RPoint : public Geometry
{
private:
    Point * Center;

public:
    RPoint(Point & p);

    bool GetIntersection(const Ray & r, float & distance);
    Vector GetNormal(Point & p);
};

class RSphere : public Geometry
{
private:
    Point                       *Center;
    unsigned int                Radius;
    static map<string, string>  mandatoryAttributes;
    static bool                 mandatoryAttributesFilled;

public:
    RSphere(Point p, unsigned int r);

    bool   GetIntersection(const Ray & r, float & distance);
    Vector GetNormal(Point & p);
    static map<string, string> & GetMandatoryAttributes();
};

class RPlan : public Geometry
{
protected:
    Point  *O, *A, *B;
    Vector *VN, *OA, *OB;

    float u, v;

public:
//     RPlan(Point o, Vector vnormal);
    RPlan(Point O, Point A, Point B);

    bool GetIntersection(const Ray & r, float & distance);
    Vector GetNormal(Point & p);
};


//TODO: implementation issue -> point A and B should recalculated to match actual coordinate (u and v)
class RTriangle : public RPlan
{
protected:
    float coord_u;
    float coord_v;

    float line_slope_a;
    float y_intersect_b;

public:
    RTriangle(Point O, Point A, Point B, float u, float v);

    bool GetIntersection(const Ray & r, float & distance);
};

class RCube : public Geometry
{
private:
    Point *O2, *A2, *B2, *C2;
//    int triangle_number = 12;
    RTriangle* triangle[12];

public:
    RCube(Point O, Point A, Point B, Point C, float side);

    bool GetIntersection(const Ray & r, float & distance);
};

#endif //_RAY_RENDERABLE_OBJ_
