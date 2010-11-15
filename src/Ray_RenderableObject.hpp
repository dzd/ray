#ifndef _RAY_RENDERABLE_OBJ_
#define _RAY_RENDERABLE_OBJ_

#include <cmath>

#include <vector>

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
    void SetVisible(bool v=true) { isVisible = v; }
    Color GetColor() {return color;}

    int GetId() {return object_id;}
};


/**
* Base class for geometry definition
*/
class Geometry
{
public:
    Geometry() {}

    virtual bool GetIntersection(Ray & r, float & distance) = 0;
    virtual Vector GetNormal(Point & p) = 0;
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

    bool GetIntersection(Ray & r, float & distance);
    Vector GetNormal(Point & p);
};

class RSphere : public Geometry
{
private:
    Point * Center;
    unsigned int      Radius;

public:
    RSphere(Point p, unsigned int r);

    bool GetIntersection(Ray & r, float & distance);
    Vector GetNormal(Point & p);
};

class RCube : public Geometry
{};

class RPlan : public Geometry
{
protected:
    Point  *origin;
    Vector *vnormal;

public:
    RPlan(Point o, Vector vnormal);

    bool GetIntersection(Ray & r, float & distance);
    Vector GetNormal(Point & p);
};


#endif //_RAY_RENDERABLE_OBJ_
