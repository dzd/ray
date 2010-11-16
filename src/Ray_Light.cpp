using namespace std;

#include "Ray_Light.hpp"

Light::Light(Point p, Color c)
{
    position    = new Point(p);
    color       = new Color(c);
}