#ifndef __RAY_LIGHT__
#define __RAY_LIGHT__

#include "Ray_Math.hpp"
#include "Ray_Color.hpp"

class Light
{
private:
    Point * position;
    Color * color;

public:
    Light(Point p, Color c);

    //TODO: return a const Point & would be better ? 
    Point GetPosition() { return *position;}
};


#endif //__RAY_LIGHT__
