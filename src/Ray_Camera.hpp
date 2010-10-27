#ifndef _RAY_Camera_
#define _RAY_Camera_

#include <list>

#include "Ray_Math.hpp"
#include "Ray_Color.hpp"

class ScreenPoint;


/**
* The camera class
**/
class Camera
{
private:
    Point   *   Center;
    Vector  *   Direction;
    int         Width;
    int         Height;
    list<ScreenPoint>   Screen;
    list<ScreenPoint>::iterator it;

    list<Color> rawImage;

    void InitDefaultScreen();

private:
    void DumpRawImage();

public:
    Camera(Point center, Vector direction, int width=640, int height=480);

    void SetDirection(Vector & v);
    void SetTarget(Point & p);
    void SetCenter(Point & p);
    void SetScreen(int w, int h);
    const Vector & GetDirection() { return *Direction;}

    int GetWidth() { return Width; }
    int GetHeight() { return Height; }

    void InitScreenIterator();
    bool GetNextRay(Ray * r);
    //ScreenPoint & GetNextScreenPoint();
    bool GetNextScreenPoint(ScreenPoint * sp);
};
/**
* This Class derives from the math Point class defined in Ray_Math.hpp
* it simply adds a color to basic points.
*/
class ScreenPoint : public Point
{
private:
    Color * c;
    int distance;

public:
    ScreenPoint(float x, float y, float z) : Point(x, y, z) {c = new Color(0,0,0); distance = -1;}
    ScreenPoint(const Point & p) : Point(p) {}
    ScreenPoint(const ScreenPoint & sp) : Point (0,0,0) {x = sp.X(); y = sp.Y(); z = sp.Z();
                                                        distance = sp.distance;
                                                        c = new Color(sp.GetColor());}

    void SetColor(const Color & color)  { c = new Color(color); }
    void SetColor(int r, int g, int b)  { c = new Color(r,g,b); }

    Color GetColor() const { return Color(*c); }

    void SetDistance(int d) { distance = d; }
    int GetDistance()       { return distance; }

    //friend ostream & operator<<(ostream & o, ScreenPoint & sp) {return o << "d:"<<sp.distance<<",color:"<<sp.c->Show();}
};

#endif //_RAY_Camera_
