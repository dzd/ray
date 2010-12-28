using namespace std;

#include "Ray_Color.hpp"

Color::Color()
{
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(unsigned char cr, unsigned char cg, unsigned char cb)
{
    r = cr;
    g = cg;
    b = cb;
}

Color::Color(int ir, int ig, int ib)
{
    r = ir;
    g = ig;
    b = ib;
}

Color::Color(const Color & c)
{
    r = c.r;
    g = c.g;
    b = c.b;
}

void Color::Add(const Color & c)
{
    r = r+c.r;
    g = g+c.g;
    b = b+c.b;

    Normalize();
}
void Color::Minus(const Color & c)
{

    if (r > c.r) { r = r -c.r; }
    else { r = 0; }

    if (g > c.g) { g = g -c.g; }
    else { g = 0; }

    if (b > c.b) { b = b -c.b; }
    else { b = 0; }

    Normalize();
}

void Color::Show()
{
    cout <<"|"<<(int)r<<"|"<<(int)g<<"|"<<(int)b<<"|"<<endl;
}


/**
 * truncate color value to values into [0,255]
 */
void Color::Normalize()
{
    if(r > 255)
        r = 255;
    if(r < 0)
        r = 0;

    if(g > 255)
        g = 255;
    if(g < 0)
        g = 0;

    if(b > 255)
        b = 255;
    if(b < 0)
        b = 0;

}

void Color::Set(unsigned char r, unsigned char g, unsigned char b)
{
    this->r =r;
    this->g =g;
    this->b =b;

    Normalize();
}


ostream & operator<<(ostream &o, Color & c) { return o << "[" << (int)c.r << "," << (int)c.g << "," << (int)c.b << "]"; }